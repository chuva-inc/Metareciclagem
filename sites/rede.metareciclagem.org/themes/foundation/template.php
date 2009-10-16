<?php
// $Id: template.php,v 1.3 2008/06/23 12:08:02 add1sun Exp $

/**
 * Override or insert PHPTemplate variables into the page templates.
 */
function foundation_preprocess_page(&$vars) {
  return $vars;
}

/**
 * Override or insert PHPTemplate variables into the node templates.
 */
function foundation_preprocess_node(&$vars) {
  // Set author information line separately from the full $submitted variable.
  $vars['authored'] = t('Submitted by') .' '. $vars['name'];
  return $vars;
}

/**
 * Override the search form (theme, not block) to remove the label.
 */
function foundation_search_theme_form($form) {
  unset($form['search_theme_form']['#title']);
  return drupal_render($form);
}
