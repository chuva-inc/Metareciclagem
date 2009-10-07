<?php
// $Id: threecol_33_34_33.inc,v 1.1.2.1 2008/12/16 21:27:58 merlinofchaos Exp $

/**
 * Implementation of hook_panels_layouts().
 */
function panels_threecol_33_34_33_panels_layouts() {
  $items['threecol_33_34_33'] = array(
    'title' => t('Three column 33/34/33'),
    'icon' => 'threecol_33_34_33.png',
    'theme' => 'panels_threecol_33_34_33',
    'css' => 'threecol_33_34_33.css',
    'panels' => array(
      'left' => t('Left side'),
      'middle' => t('Middle column'),
      'right' => t('Right side')
     ),
  );

  return $items;
}
