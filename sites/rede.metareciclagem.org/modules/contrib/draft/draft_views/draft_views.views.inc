<?php
// $Id: draft_views.views.inc,v 1.1.2.7 2009/09/25 20:29:12 darrenferguson Exp $

/**
 * @file
 * Provide views data and handlers for draft.module
 */
/**
 * Implementation of hook_views_handlers().
 */
function draft_views_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'draft_views') .'/includes',
    ),
    'handlers' => array(
      'draft_views_views_handler_field_date_drafts_updated' => array(
        'parent' => 'views_handler_field_date',
      ),
      'draft_views_views_handler_field_draft_node_type' => array(
        'parent' => 'views_handler_field',
      ),
      'draft_views_views_handler_field_draft_data' => array(
        'parent' => 'views_handler_field',
      ),
      'draft_views_views_handler_field_draft_view' => array(
        'parent' => 'views_handler_field',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_data()
 */
function draft_views_views_data() {
  // field group
  $data['drafts']['table']['group']  = t('Draft');

  // advertise as base table
  $data['drafts']['table']['base'] = array(
    'field' => 'draft_id',
    'title' => t('Draft'),
    'help' => t("Drafts table holding all draft content not yet published"),
    'weight' => -10,
  );

  // table joins
  $data['drafts']['table']['join'] = array(
    'users' => array(
      'left_field' => 'uid',
      'field' => 'uid',
      'type' => 'INNER'
    ),
    'node_type' => array(
      'left_field' => 'node_type',
      'field' => 'type',
      'type' => 'INNER'
    )
  );

  // draft_id
  $data['drafts']['draft_id'] = array(
    'title' => t('Draft ID'),
    'help' => t('The Draft ID'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
       'handler' => 'views_handler_sort',
    ),
  );

  // uid
  $data['drafts']['uid'] = array(
    'title' => t('User ID'),
    'help' => t("The user's ID"),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
       'handler' => 'views_handler_sort',
    ),
  );

  // node type
  $data['drafts']['node_type'] = array(
    'title' => t('Node Type'),
    'help' => t('Node Type for the draft'),
    'field' => array(
      'handler' => 'draft_views_views_handler_field_draft_node_type',
      'click sortable' => TRUE,
    ),
    'sort' => array(
       'handler' => 'views_handler_sort',
    ),
  );

  // title for the draft
  $data['drafts']['title'] = array(
    'title' => t('Title'),
    'help' => t('Draft Title'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
       'handler' => 'views_handler_sort',
    ),
  );

  // body for the draft
  $data['drafts']['body'] = array(
    'title' => t('Body'),
    'help' => t('Draft Body'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
       'handler' => 'views_handler_sort',
    ),
  );

  // data saved about the draft
  $data['drafts']['data'] = array(
    'title' => t('Data'),
    'help' => t('Data'),
    'field' => array(
      'handler' => 'draft_views_views_handler_field_draft_data',
      'click sortable' => TRUE,
    ),
    'sort' => array(
       'handler' => 'views_handler_sort',
    ),
  );

  // updated
  $data['drafts']['updated'] = array(
    'title' => t('Updated'),
    'help' => t('Last update for draft'),
    'field' => array(
      'handler' => 'draft_views_views_handler_field_date_drafts_updated',
      'click sortable' => TRUE,
    ),
    'sort' => array(
       'handler' => 'views_handler_sort',
    ),
  );

  // Cron Remove flag
  $data['drafts']['cron_remove'] = array(
    'title' => t('Cron Remove'),
    'help' => t('Remove from Cron'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'sort' => array(
       'handler' => 'views_handler_sort',
    ),
  );

  // this is a link
  $data['drafts']['view_draft'] = array(
    'field' => array(
      'title' => t('View Draft'),
      'help' => t('Provide a simple link to view the draft.'),
      'handler' => 'draft_views_views_handler_field_draft_view',
    ),
  );
  return $data;
}
