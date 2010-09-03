<?php
// $Id

/**
 * Draft Module administration settings
 */
function draft_admin_settings() {
  $form['draft'] = array('#type' => 'fieldset', '#title' => t('Draft Settings'), '#collapsible' => TRUE, '#collapsed' => FALSE);
  $form['draft']['draft_autosave_interval'] = array(
    '#type' => 'textfield',
    '#title' => t('Draft Autosave Interval'),
    '#default_value' => variable_get('draft_autosave_interval', 30),
    '#description' => t('Time (Seconds) interval between automatic savings of the form'),
    '#size' => 6,
  );
  $form['draft']['draft_form_elements_ignore'] = array(
    '#type' => 'textfield',
    '#title' => t('Ignore form elements'),
    '#default_value' => variable_get('draft_form_elements_ignore', 'op|form_token|form_build_id'),
    '#description' => t('List of form elements spilt by "|" that we do not wish to save i.e. form token, op buttons etc'),
    '#maxlength' => '1024',
  );
  $form['draft']['draft_disable_autosave'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable draft autosave'),
    '#default_value' => variable_get('draft_disable_autosave', 0),
    '#description' => t('Check if you wish to completely disable autosave for drafts, will not show up in user form as option either'),
  );
  $form['draft']['draft_on_edit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow drafts when editing'),
    '#default_value' => variable_get('draft_on_edit', 0),
    '#description' => t('If checked then the module will allow you to save as draft when editing an already existing node'),
  );
  $form['draft']['draft_cron_remove_disabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable cron removal of drafts'),
    '#default_value' => variable_get('draft_cron_remove_disabled', 0),
    '#description' => t('If checked then cron will not remove any drafts from the system and they will continually accumulate'),
  );
  $form['draft']['draft_cron_remove_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Amount of time (Days) a draft can stay in the system without being updated'),
    '#default_value' => variable_get('draft_cron_remove_timeout', 1),
    '#description' => t('When a draft is originally created if the cron timeout is never set to 1 then it has never been updated so we need to allow these to remain for a little amount of time before they are removed'),
    '#size' => 6,
  );
  $form['draft']['draft_php_view_pager_count'] = array(
    '#type' => 'textfield',
    '#title' => t('Numer of drafts per page in Draft List'),
    '#default_value' => variable_get('draft_php_view_pager_count', 20),
    '#description' => t('This is the number of drafts you will see on the php version of the draft list using the pager query'),
    '#size' => 6,
  );
  $form['draft']['draft_php_view_display_columns'] = array(
    '#type' => 'checkboxes',
    '#title' => t('PHP View Display Fields'),
    '#default_value' => variable_get('draft_php_view_display_columns', array()),
    '#options' => _draft_php_view_display_fields(),
    '#description' => t('Check the fields you wish to see displayed in the PHP View'),
  );
  return system_settings_form($form);
}

/**
 * Return an associative array of the available display fields
 */
function _draft_php_view_display_fields() {
  return array(
    'node_type' => t('Type'),
    'uid' => t('Username'),
    'title' => t('Title'),
    'body' => t('Body'),
    'updated' => t('Last Update'),
    'cron_remove' => t('Cron Remove')
  );
}

