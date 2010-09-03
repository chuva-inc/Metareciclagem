<?php
// $Id: draft_views.views_default.inc,v 1.1.2.7 2009/09/25 20:29:12 darrenferguson Exp $
/**
 * @file
 * Contains default views on behalf of the draft_views module.
 */

/**
 * Implementation of hook_default_view_views().
 */
function draft_views_views_default_views() {
$view = new view;
$view->name = 'draft_list';
$view->description = 'Draft List';
$view->tag = 'draft';
$view->view_php = '';
$view->base_table = 'users';
$view->is_cacheable = FALSE;
$view->api_version = 2;
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->override_option('fields', array(
  'view_draft' => array(
    'label' => 'View Draft',
    'exclude' => 0,
    'id' => 'view_draft',
    'table' => 'drafts',
    'field' => 'view_draft',
    'relationship' => 'none',
  ),
  'node_type' => array(
    'label' => 'Type',
    'exclude' => 0,
    'id' => 'node_type',
    'table' => 'drafts',
    'field' => 'node_type',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
  'title' => array(
    'label' => 'Title',
    'exclude' => 0,
    'id' => 'title',
    'table' => 'drafts',
    'field' => 'title',
    'relationship' => 'none',
  ),
  'body' => array(
    'label' => 'Body',
    'exclude' => 1,
    'id' => 'body',
    'table' => 'drafts',
    'field' => 'body',
    'relationship' => 'none',
  ),
  'updated' => array(
    'id' => 'updated',
    'table' => 'drafts',
    'field' => 'updated',
  ),
  'cron_remove' => array(
    'label' => 'Cron Remove',
    'exclude' => 1,
    'id' => 'cron_remove',
    'table' => 'drafts',
    'field' => 'cron_remove',
    'relationship' => 'none',
  ),
  'draft_id' => array(
    'label' => 'Draft ID',
    'exclude' => 1,
    'id' => 'draft_id',
    'table' => 'drafts',
    'field' => 'draft_id',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
  ),
));
$handler->override_option('sorts', array(
  'updated' => array(
    'order' => 'DESC',
    'id' => 'updated',
    'table' => 'drafts',
    'field' => 'updated',
    'relationship' => 'none',
  ),
));
$handler->override_option('arguments', array(
  'uid' => array(
    'default_action' => 'default',
    'style_plugin' => 'default_summary',
    'style_options' => array(),
    'wildcard' => 'all',
    'wildcard_substitution' => 'All',
    'title' => 'Draft List',
    'default_argument_type' => 'php',
    'default_argument' => '',
    'validate_type' => 'none',
    'validate_fail' => 'not found',
    'break_phrase' => 0,
    'not' => 0,
    'id' => 'uid',
    'table' => 'users',
    'field' => 'uid',
    'override' => array(
      'button' => 'Override',
    ),
    'relationship' => 'none',
    'default_options_div_prefix' => '',
    'default_argument_user' => 0,
    'default_argument_fixed' => '',
    'default_argument_php' => 'global $user;
                    return $user->uid;',
    'validate_argument_node_type' => array(
      'blog' => 0,
      'event' => 0,
      'og' => 0,
      'page' => 0,
      'profile' => 0,
      'story' => 0,
      'xmppchat' => 0,
    ),
    'validate_argument_node_access' => 0,
    'validate_argument_nid_type' => 'nid',
    'validate_argument_is_member' => 0,
    'validate_argument_vocabulary' => array(
      '4' => 0,
      '1' => 0,
      '26' => 0,
      '20' => 0,
      '24' => 0,
      '23' => 0,
      '25' => 0,
    ),
    'validate_argument_type' => 'tid',
    'validate_argument_php' => '',
  ),
));
$handler->override_option('access', array(
  'type' => 'perm',
  'role' => array(),
  'perm' => 'access save as draft',
));
$handler->override_option('title', 'Draft List');
$handler->override_option('use_pager', 'mini');
$handler->override_option('style_plugin', 'table');
$handler->override_option('style_options', array(
  'grouping' => '',
  'override' => 1,
  'sticky' => 0,
  'order' => 'asc',
  'columns' => array(
    'draft_id' => 'draft_id',
    'node_type' => 'node_type',
    'updated' => 'updated',
    'name' => 'name',
  ),
  'info' => array(
    'draft_id' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'node_type' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'updated' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'name' => array(
      'sortable' => 1,
      'separator' => '',
    ),
  ),
  'default' => 'name',
));
$handler = $view->new_display('page', 'Page', 'page_1');
$handler->override_option('path', 'draft/list');
$handler->override_option('menu', array(
  'type' => 'none',
  'title' => 'Drafts',
  'weight' => '0',
  'name' => 'navigation',
));
$handler->override_option('tab_options', array(
  'type' => 'none',
  'title' => '',
  'weight' => 0,
));

$views[$view->name] = $view;

return $views;
}
