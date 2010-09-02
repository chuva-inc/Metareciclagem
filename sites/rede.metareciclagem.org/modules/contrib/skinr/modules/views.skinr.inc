<?php
// $Id$
/**
 * @file
 * Provide skinr handling for node.module
 */

/**
 * @defgroup skinr_node_module node.module handlers
 *
 * @{
 */

/**
 * Implementation of hook_skinr_data().
 */
function views_skinr_data() {
  $data['views']['form']['views_ui_edit_display_form'] = array(
    'index_handler' => 'views_skinr_form_index_handler',
    'access_handler' => 'views_skinr_access_handler_display',
    'data_handler' => 'views_skinr_data_handler',
    'submit_handler' => 'views_skinr_submit_handler_display',
    'preprocess_hook' => 'views_view',
    'title' => t('Views style settings'),
    'skinr_weight' => 0,
    'collapsed' => FALSE,
  );
  $data['views']['form']['views_ui_edit_view_form'] = array(
    'access_handler' => 'views_skinr_access_handler_view',
    'submit_handler' => 'views_skinr_submit_handler_view',
  );
  $data['views']['preprocess']['views_view'] = array(
    'index_handler' => 'views_skinr_preprocess_index_handler',
  );

  return $data;
}

/**
 * Skinr form index handler.
 *
 * @param $op
 *   What kind of action is being performed. Possible values:
 *   - "form": the form elements for Skinr are being inserted in a form
 *   - "submit": the form has been submitted.
 * @param &$form
 *   - For "form", passes in the $form parameter from hook_form_alter().
 *   - For "submit", passes in the $form parameter from hook_form_submit().
 * @param $form_state
 *   - For "form", passes in the $form_state parameter from hook_form_alter().
 *   - For "submit", passes in the $form_state parameter from hook_form_submit().
 * @return
 *   The index where we can find our values in Skinrs data structure.
 */
function views_skinr_form_index_handler($op, &$form, $form_state) {
  switch ($op) {
    case 'form':
    case 'submit':
      return 'view-'. $form_state['view']->name .'-display-'. $form_state['display_id'];
  }
}

/**
 * Skinr access handler.
 *
 * @param $op
 *   What kind of action is being performed. Possible values:
 *   - "access skinr": access to edit skinr's selector
 *   - "access skinr classes": access to edit skinr's additional classes
 * @param &$form
 *   Passes in the $form parameter from hook_form_alter().
 * @param $form_state
 *   Passes in the $form_state parameter from hook_form_alter().
 * @return
 *   TRUE if we get access, FALSE if we don't.
 */
function views_skinr_access_handler_display($op, &$form, $form_state) {
  if ($access = skinr_access_handler($op, $form, $form_state)) {
    // Views uses the same form_id for all forms, but it sets a $section
    // variable to distinguish between them. So only show the skinr settings
    // form on the style options form.
    if ($form_state['section'] != 'style_options') {
      $access = FALSE;
    }
  }

  return $access;
}

function views_skinr_access_handler_view($op, &$form, $form_state) {
  // We don't want the skinr settings form to appear on this form. We only want
  // to intercept it so we can save our cached data.

  // Since we're not using the form, we won't get our form submitter, so let's
  // add it manually.

  // Only add submit handler once
  if (!in_array('skinr_form_submit', $form['#submit'])) {
    $form['#submit'][] = 'skinr_form_submit';
  }
  // Special for views
  if (isset($form['buttons']['save']['#submit']) && !in_array('skinr_form_submit', $form['buttons']['save']['#submit'])) {
    $form['buttons']['save']['#submit'][] = 'skinr_form_submit';
  }
  if (isset($form['buttons']['cancel']['#submit']) && !in_array('skinr_form_submit', $form['buttons']['cancel']['#submit'])) {
    // Need to make this happen before views' submit handler because it hijacks
    // things and does a drupal_goto(). That effectively prevents any other
    // submit handlers from being processed.
    array_unshift($form['buttons']['cancel']['#submit'], 'skinr_form_submit');
  }

  return FALSE;
}

/**
 * Skinr data handler.
 * This is the data that populates the skinr form.
 *
 * @param &$form
 *   Passes in the $form parameter from hook_form_submit().
 * @param $form_state
 *   Passes in the $form_state parameter from hook_form_submit().
 * @param $module
 *   The module that is currently being processed.
 * @param $form_settings
 *   The settings from hook_skinr_data() for the form that's currently being
 *   processed.
 * @return
 *   TRUE if we get access, FALSE if we don't.
 */
function views_skinr_data_handler(&$form, $form_state, $module, $form_settings) {
  // Ensure we have the required index_handler
  if (empty($form_settings['index_handler'])) {
    trigger_error(sprintf("No index_handler was found for form_id '%s' in module '%s'.", $form_id, $module), E_USER_ERROR);
  }
  $index = skinr_handler('form_index_handler', 'form', $form_settings['index_handler'], $form, $form_state);

  // Fetch skinr data for this view from cache
  views_include('cache');

  if ($skinr_data = views_object_cache_get('skinr', $form_state['view']->name)) {
    if (isset($skinr_data[$index])) {
      return $skinr_data[$index];
    }
    else {
      return array();
    }
  }

  // No data exists in cache, so let's grab it from the regular source
  return skinr_get($module, $index);
}

/**
 * Skinr submit handler.
 *
 * @param $op
 *   What kind of action is being performed. Possible values:
 *   - "access skinr": access to edit skinr's selector
 *   - "access skinr classes": access to edit skinr's additional classes
 * @param &$form
 *   Passes in the $form parameter from hook_form_alter().
 * @param $form_state
 *   Passes in the $form_state parameter from hook_form_alter().
 * @return
 *   TRUE if we get access, FALSE if we don't.
 */
function views_skinr_submit_handler_display(&$form, $form_state, $module, $form_settings) {
  if (isset($form_state['values']['skinr_'. $module]) || isset($form_state['values']['skinr_'. $module .'_additional'])) {
    $hook  = $module;
    $key   = skinr_handler('form_index_handler', 'submit', $form_settings['index_handler'], $form, $form_state);
    $value = _skinr_array_strip_empty($form_state['values']['skinr_'. $module]);
    if (isset($form_state['values']['skinr_'. $module .'_additional'])) {
      $form_state['values']['skinr_'. $module .'_additional'] = trim($form_state['values']['skinr_'. $module .'_additional']);
      if (!empty($form_state['values']['skinr_'. $module .'_additional'])) {
        $value['_additional'] = trim($form_state['values']['skinr_'. $module .'_additional']);
      }
    }

    if (empty($key)) {
      // We didn't receive a valid key, so raise an error
      drupal_set_message(t("Skinr settings weren't saved due to an error."), 'error');
    }

    // Save skinr_settings for this view in cache
    views_include('cache');

    if (!$skinr = views_object_cache_get('skinr', $form_state['view']->name)) {
      $skinr = array();
      // Fetch skinr data
      $skinr = skinr_get();
      foreach ($skinr[$module] as $skinr_key => $skinr_value) {
        if (substr($skinr_key, 0, strlen('view-'. $form_state['view']->name)) == 'view-'. $form_state['view']->name) {
          $skinr_data[$skinr_key] = $skinr_value;
        }
      }
    }
    $skinr[$key] = $value;
    views_object_cache_set('skinr', $form_state['view']->name, $skinr);
  }
}

function views_skinr_submit_handler_view(&$form, $form_state, $module, $form_settings) {
  switch ($form_state['values']['op']) {
    case 'Save':
      // Fetch skinr data for this view from cache
      views_include('cache');

      if ($skinr = views_object_cache_get('skinr', $form_state['view']->name)) {
        $hook = $module;
        foreach ($skinr as $key => $value) {
          skinr_set($hook, $key, $value);
        }
        views_object_cache_clear('skinr', $form_state['view']->name);
      }
      break;
    case 'Cancel':
      // Remove our data from views cache
      views_include('cache');

      views_object_cache_clear('skinr', $form_state['view']->name);
      break;
  }
}

/**
 * Skinr preprocess index handler.
 *
 * @param &$vars
 *   Passes in the $vars parameter from module_preprocess().
 * @return
 *   The index where we can find our values in Skinrs data structure.
 */
function views_skinr_preprocess_index_handler(&$vars) {
  return 'view-'. $vars['view']->name .'-display-'. $vars['display_id'];
}

/**
 * @}
 */
