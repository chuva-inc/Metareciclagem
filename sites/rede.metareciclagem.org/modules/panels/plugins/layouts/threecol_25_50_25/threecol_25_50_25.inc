<?php
// $Id: threecol_25_50_25.inc,v 1.1.2.2 2009/04/29 03:19:13 merlinofchaos Exp $

/**
 * implementation of hook_panels_layouts
 */
function panels_threecol_25_50_25_panels_layouts() {
  $items['threecol_25_50_25'] = array(
    'title' => t('Three column 25/50/25'),
    'icon' => 'threecol_25_50_25.png',
    'theme' => 'panels_threecol_25_50_25',
    'theme arguments' => array('id', 'content'),
    'css' => 'threecol_25_50_25.css',
    'panels' => array(
      'left' => t('Left side'),
      'middle' => t('Middle column'),
      'right' => t('Right side')
    ),
  );

  return $items;
}

