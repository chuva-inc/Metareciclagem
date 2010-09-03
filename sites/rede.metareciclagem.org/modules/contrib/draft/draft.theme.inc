<?php
// $Id

/**
 * Theme function to allow us to always get the js into the system
 */
function theme_draft_save_as_button($element = NULL) {
  global $user;

  if (!empty($element['#attributes']['node'])) {
    $node = $element['#attributes']['node'];
    unset($element['#attributes']['node']);
  }
  // adding the pertinent javascript files to the page
  drupal_add_js(DRAFT_PATH .'/jquery.field.js');
  drupal_add_css(DRAFT_PATH .'/draft.css');
  drupal_add_js(DRAFT_PATH .'/draft.js');
  // setting the javascript settings we will require in order to utilize saving the form
  if (isset($node->draft_form_data)) {
    $settings['draft']['form_data'] = unserialize($node->draft_form_data);
  }
  // Determine if we have to populate the draft or not this time
  if (isset($node->draft_populate_trigger)) {
    $settings['draft']['draft_populate_trigger'] = 0;
  }
  $settings['draft']['form_id'] = 'node-form';
  $settings['draft']['autosave'] = 0;
  $settings['draft']['img_url'] = url('draft/images');
  // User entered input so do checking on it to make sure we get a valid number
  $interval = (int) variable_get('draft_autosave_interval', 30);
  if (!is_numeric($interval)) {
    $interval = 30;
  }
  $settings['draft']['interval'] = $interval * 1000;
  $settings['draft']['url'] = url('draft/save');
  $settings['draft']['button_id'] = 'edit-save-as-draft';
  $settings['draft']['form_elements_ignore'] = variable_get('draft_form_elements_ignore', 'op|form_token|form_build_id');
  $settings['draft']['node_type'] = $node->type;
  // This is for when we are in Edit Mode so we can send the node id back with the draft
  if (!empty($node->nid)) {
    $settings['draft']['node_id'] = $node->nid;
  }
  // checking to see if autosave is enabled or not for this account
  if (!variable_get('draft_disable_autosave', 0) && variable_get('draft_autosave_'. $user->uid, 0)) {
    drupal_add_js('Drupal.draft.saveTimeout();', 'inline');
    // setting the autosave interval if the user has it set in their account since it can
    // over ride the administrator autosave timeout incase the user wishes it to be longer or shorter
    // Do checking on the variable to make sure we get a valid number
    if (($interval = variable_get('draft_autosave_interval_'. $user->uid, 0))) {
      if (is_numeric($interval) && $interval > 0) {
        $settings['draft']['interval'] = $interval * 1000;
      }
    }
    $settings['draft']['autosave'] = 1;
  }
  drupal_add_js($settings, 'setting');
  return theme_button($element);
}
