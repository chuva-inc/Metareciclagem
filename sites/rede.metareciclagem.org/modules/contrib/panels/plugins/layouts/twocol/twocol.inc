<?php
// $Id: twocol.inc,v 1.1.2.1 2008/12/16 21:27:58 merlinofchaos Exp $

/**
 * Implementation of hook_panels_layouts().
 */
function panels_twocol_panels_layouts() {
  $items['twocol'] = array(
    'title' => t('Two column'),
    'icon' => 'twocol.png',
    'theme' => 'panels_twocol',
    'css' => 'twocol.css',
    'panels' => array(
      'left' => t('Left side'),
      'right' => t('Right side')
    ),
  );

  return $items;
}