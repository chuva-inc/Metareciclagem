<?php
// $Id

/**
 * Menu callback for displaying drafts in the system
 */
function draft_list() {
  global $user;

  $node_types = node_get_types('names');
  $display_fields = variable_get('draft_php_view_display_columns', array());
  $entry = array();
  // retrieving the archived conversations for this particular temporary node type
  $header[] = array('data' => t('View Draft'), 'field' => 'draft_id');
  if (isset($display_fields['node_type']) && $display_fields['node_type'] === 'node_type') {
    $header[] = array('data' => t('Type'), 'field' => 'node_type');
  }
  if (isset($display_fields['uid']) && $display_fields['uid'] === 'uid') {
    $header[] = array('data' => t('Username'), 'field' => 'uid');
  }
  if (isset($display_fields['title']) && $display_fields['title'] === 'title') {
    $header[] = array('data' => t('Title'), 'field' => 'title');
  }
  if (isset($display_fields['body']) && $display_fields['body'] === 'body') {
    $header[] = array('data' => t('Body'), 'field' => 'body');
  }
  if (isset($display_fields['updated']) && $display_fields['updated'] === 'updated') {
    $header[] = array('data' => t('Last Updated'), 'field' => 'updated', 'sort' => 'desc');
  }
  if (isset($display_fields['cron_remove']) && $display_fields['cron_remove'] === 'cron_remove') {
    $header[] = array('data' => t('Cron Remove'), 'field' => 'cron_remove');
  }
  $sql = sprintf("SELECT * FROM {drafts} WHERE uid = %d". tablesort_sql($header), $user->uid);
  $count_sql = sprintf("SELECT DISTINCT draft_id FROM {drafts} WHERE uid = %d", $user->uid);
  $result = pager_query($sql, 20, NULL, $count_sql);
  while ($row = db_fetch_object($result)) {
    $data = unserialize($row->data);
    if (isset($data['node_id_from_server']) && is_numeric($data['node_id_from_server'])) {
      $output = l(t('View'), 'node/'. $data['node_id_from_server'] .'/edit', array('query' => array('draft_id' => $row->draft_id)));
    }
    else {
      $output = l(t('View'), 'node/add/'. str_replace("_", "-", $row->node_type), array('query' => array('draft_id' => $row->draft_id)));
    }
    $output .= ' | '. l(t('Delete'), 'draft/remove/'. $row->draft_id);
    $entry[$row->draft_id]['draft_id'] = $output;
    if (isset($display_fields['node_type']) && $display_fields['node_type'] === 'node_type') {
      $entry[$row->draft_id]['node_type'] = draft_tt("nodetype:type:$row->node_type:name", node_get_types('name', $row->node_type));
    }
    if (isset($display_fields['uid']) && $display_fields['uid'] === 'uid') {
      $cuser = user_load(array('uid' => $row->uid));
      $entry[$row->draft_id]['uid'] = $user->name;
    }
    if (isset($display_fields['title']) && $display_fields['title'] === 'title') {
      $entry[$row->draft_id]['title'] = $row->title;
    }
    if (isset($display_fields['body']) && $display_fields['body'] === 'body') {
      $entry[$row->draft_id]['body'] = $row->body;
    }
    if (isset($display_fields['updated']) && $display_fields['updated'] === 'updated') {
      $entry[$row->draft_id]['updated'] = format_date($row->updated, 'small');
    }
    if (isset($display_fields['cron_remove']) && $display_fields['cron_remove'] === 'cron_remove') {
      $entry[$row->draft_id]['cron_remove'] = ($row->cron_remove) ? t('No') : t('Yes');
    }
  }
  $output = theme('table', $header, $entry);
  $count = variable_get('draft_php_view_pager_count', 20);
  if (!is_numeric($count)) {
    $count = 20;
  }
  $output .= theme('pager', NULL, $count, 0);
  return $output;
}

/**
 * Menu callback for removing the draft from the database
 *
 * @param $draft_id
 *      ID of draft you wish to remove
 */
function draft_remove($draft_id = NULL) {
  if ($draft_id && is_numeric($draft_id)) {
    return drupal_get_form('draft_remove_form', $draft_id);
  }
  else {
    drupal_set_message(t('No draft id was received by the system'));
    $redirect = 'draft/list';
    if (module_exists('draft_views')) {
      $redirect = variable_get('draft_views_redirect_url', 'draft/list');
    }
    drupal_goto($redirect);
  }
}

/**
 * Confirmation form for removing the draft
 *
 * @param $form_state
 *      Array holding the initial form state
 * @param $draft_id
 *      ID of the draft we wish to remove
 */
function draft_remove_form(&$form_state, $draft_id) {
  $redirect = 'draft/list';
  if (module_exists('draft_views')) {
    $redirect = variable_get('draft_views_redirect_url', 'draft/list');
  }
  $form['draft_id'] = array('#type' => 'hidden', '#value' => $draft_id);
  return confirm_form($form,
         t('Are you sure you wish to remove the draft?'),
         $redirect,
         NULL,
         t('Delete'),
         t('Cancel'));
}

/**
 * Form Submit handler for removing the draft
 */
function draft_remove_form_submit($form, $form_state) {
  if (isset($form_state['values']['draft_id']) && is_numeric($form_state['values']['draft_id'])) {
    db_query("DELETE FROM {drafts} WHERE draft_id = %d", $form_state['values']['draft_id']);
    drupal_set_message(t('Draft successfully removed from the system'));
  }
  else {
    drupal_set_message(t('No draft id was received by the system'));
  }
  $redirect = 'draft/list';
  if (module_exists('draft_views')) {
    $redirect = variable_get('draft_views_redirect_url', 'draft/list');
  }
  drupal_goto($redirect);
}

/**
 * Ajax handler to save the draft into the system
 */
function draft_save() {
  global $user;
  $output = '';
  $node_id = $title = $body = NULL;
  // added per Flexer (Claudio)'s suggestion so the Devel module will not break the draft id being returned
  $GLOBALS['devel_shutdown'] = FALSE;
  // getting the type of node we need
  $type = $_POST['node_type'];
  $draft_id = $_POST['draft_id'];
  unset($_POST['node_type'], $_POST['draft_id']);

  if (module_exists('content')) {
    // checking for the title field to determine if it is in the POST array
    $title_field = variable_get('save_as_draft_title_'. $type, 'title');
    if (isset($_POST[trim($title_field)])) {
      $title = $_POST[trim($title_field)];
    }
    // checking for the body field to determine if it is in the POST array
    $body_field = variable_get('save_as_draft_body_'. $type, 'body');
    if (isset($_POST[trim($body_field)]) || isset($_POST[trim(str_replace("_field", "", $body_field))])) {
      if (isset($_POST[trim($body_field)])) {
        $body = $_POST[trim($body_field)];
      }
      else {
        $body = $_POST[trim(str_replace("_field", "", $body_field))];
      }
    }
  }
  else {
    // Fallback and try to check if title or body is set in the POST array
    if (isset($_POST['title'])) {
      $title = $_POST['title'];
    }
    if (isset($_POST['body'])) {
      $body = $_POST['body'];
    }
  }
  // data coming in via HTTP POST and we are serializing it
  $data = serialize($_POST);

  if (is_null($draft_id) || !is_numeric($draft_id)) {
    $array = array('node_type' => $type, 'uid' => $user->uid, 'updated' => time(), 'title' => $title, 'body' => $body, 'data' => $data, 'cron_remove' => 1);
    drupal_write_record('drafts', $array);
    $draft_id = $array['draft_id'];
  }
  else {
    $array = array('draft_id' => $draft_id, 'updated' => time(), 'title' => $title, 'body' => $body, 'data' => $data, 'cron_remove' => 1);
    // Perform the update but if an error occurs then make sure we correctly do the insert into the table
    if (drupal_write_record('drafts', $array, array('draft_id')) === FALSE) {
      $array = array('draft_id' => $draft_id, 'node_type' => $type, 'uid' => $user->uid, 'updated' => time(), 'title' => $title, 'body' => $body, 'data' => $data, 'cron_remove' => 1);
      drupal_write_record('drafts', $array);
    }
  }
  print $draft_id;
  exit;
}
