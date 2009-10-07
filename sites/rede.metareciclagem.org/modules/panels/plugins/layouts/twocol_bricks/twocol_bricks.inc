<?php
// $Id: twocol_bricks.inc,v 1.1.2.1 2008/12/16 21:27:59 merlinofchaos Exp $

/**
 * @file twocol_bricks.inc
 *
 * Implementation for the two column bricked layout
 */

/**
 * Implementation of hook_panels_layouts().
 */
function panels_twocol_bricks_panels_layouts() {
  $items['twocol_bricks'] = array(
    'title' => t('Two column bricks'),
    'icon' => 'twocol_bricks.png',
    'theme' => 'panels_twocol_bricks',
    'css' => 'twocol_bricks.css',
    'panels' => array(
      'top' => t('Top'),
      'left_above' => t('Left above'),
      'right_above' => t('Right above'),
      'middle' => t('Middle'),
      'left_below' => t('Left below'),
      'right_below' => t('Right below'),
      'bottom' => t('Bottom'),
    ),
  );
  return $items;
}

