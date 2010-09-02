<?php

/**
 * Helper to implementation of hook_context_default_contexts().
 */
function _metarec_blog_context_default_contexts() {
  $items = array();

  $items[] = array(
    'namespace' => 'context_ui',
    'attribute' => 'page',
    'value' => 'blog',
    'description' => 'Página de blog',
    'path' => array(
      'blog' => 'blog',
      'blog/*' => 'blog/*',
    ),
    'menu' => 'blog',
    'theme_section' => array(
      'class' => 'blog',
    ),
    'theme_regiontoggle' => array(
      '0' => 'sidebar_first',
    ),
    'block' => array(
      'views_blog_5-block_1' => array(
        'module' => 'views',
        'delta' => 'blog_5-block_1',
        'weight' => 65,
        'region' => 'sidebar_second',
        'status' => '0',
        'label' => 'blog_5: Bloco',
        'type' => 'context_ui',
      ),
      'tagadelic_1' => array(
        'module' => 'tagadelic',
        'delta' => '1',
        'weight' => 66,
        'region' => 'sidebar_second',
        'status' => '0',
        'label' => 'Assuntos deste site',
        'type' => 'context_ui',
      ),
    ),
  );
  return $items;
}
