<?php

class LibhoursPeriodController extends EntityAPIController {

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $build = parent::buildContent($entity, $view_mode, $langcode, $content);
    // Add Period elements to the $build render array.
    $build['period_name'] = array(
      '#type' => 'markup',
      '#markup' => check_plain($entity->period_name),
      '#prefix' => '<div class="period-name">',
      '#suffix' => '</div>',
    );
    $build['start_date'] = array(
      '#type' => 'markup',
      '#markup' => format_date($entity->start_date),
      '#prefix' => '<div class="period-start-date">',
      '#suffix' => '</div>',
    );
    $build['end_date'] = array(
      '#type' => 'markup',
      '#markup' => format_date($entity->end_date),
      '#prefix' => '<div class="period-end-date">',
      '#suffix' => '</div>',
    );

    return $build;
  }

  public function save($entity, DatabaseTransaction $transaction = NULL) {
    // Force start datetime to 00:00:00 and end datetime to 23:59:59
    $entity->start_date = $this->startOfDay($entity->start_date);
    $entity->end_date = $this->endOfDay($entity->end_date);

    // Save the modified entity
    parent::save($entity, $transaction);
  }

  public function startOfDay($timestamp) {
    // Returns timestamp for datetime with time set to 00:00:00
    return strtotime('midnight', $timestamp);
  }

  public function endOfDay($timestamp) {
    // Returns timestamp for datetime with time set to 23:59:59
    return strtotime('tomorrow', $timestamp) - 1;
  }
}
