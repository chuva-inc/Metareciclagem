<?php
// $Id: template.php,v 1.21 2009/08/12 04:25:15 johnalbin Exp $

/**
 * @file
 * Contains theme override functions and preprocess functions for the theme.
 *
 * ABOUT THE TEMPLATE.PHP FILE
 *
 *   The template.php file is one of the most useful files when creating or
 *   modifying Drupal themes. You can add new regions for block content, modify
 *   or override Drupal's theme functions, intercept or make additional
 *   variables available to your theme, and create custom PHP logic. For more
 *   information, please visit the Theme Developer's Guide on Drupal.org:
 *   http://drupal.org/theme-guide
 *
 * OVERRIDING THEME FUNCTIONS
 *
 *   The Drupal theme system uses special theme functions to generate HTML
 *   output automatically. Often we wish to customize this HTML output. To do
 *   this, we have to override the theme function. You have to first find the
 *   theme function that generates the output, and then "catch" it and modify it
 *   here. The easiest way to do it is to copy the original function in its
 *   entirety and paste it here, changing the prefix from theme_ to metarec_.
 *   For example:
 *
 *     original: theme_breadcrumb()
 *     theme override: metarec_breadcrumb()
 *
 *   where metarec is the name of your sub-theme. For example, the
 *   zen_classic theme would define a zen_classic_breadcrumb() function.
 *
 *   If you would like to override any of the theme functions used in Zen core,
 *   you should first look at how Zen core implements those functions:
 *     theme_breadcrumbs()      in zen/template.php
 *     theme_menu_item_link()   in zen/template.php
 *     theme_menu_local_tasks() in zen/template.php
 *
 *   For more information, please visit the Theme Developer's Guide on
 *   Drupal.org: http://drupal.org/node/173880
 *
 * CREATE OR MODIFY VARIABLES FOR YOUR THEME
 *
 *   Each tpl.php template file has several variables which hold various pieces
 *   of content. You can modify those variables (or add new ones) before they
 *   are used in the template files by using preprocess functions.
 *
 *   This makes THEME_preprocess_HOOK() functions the most powerful functions
 *   available to themers.
 *
 *   It works by having one preprocess function for each template file or its
 *   derivatives (called template suggestions). For example:
 *     THEME_preprocess_page    alters the variables for page.tpl.php
 *     THEME_preprocess_node    alters the variables for node.tpl.php or
 *                              for node-forum.tpl.php
 *     THEME_preprocess_comment alters the variables for comment.tpl.php
 *     THEME_preprocess_block   alters the variables for block.tpl.php
 *
 *   For more information on preprocess functions and template suggestions,
 *   please visit the Theme Developer's Guide on Drupal.org:
 *   http://drupal.org/node/223440
 *   and http://drupal.org/node/190815#template-suggestions
 */


/**
 * Implementation of HOOK_theme().
 */
function metarec_theme(&$existing, $type, $theme, $path) {
  $hooks = zen_theme($existing, $type, $theme, $path);
  // Add your theme hooks like this:
  /*
  $hooks['hook_name_here'] = array( // Details go here );
  */
  // @TODO: Needs detailed comments. Patches welcome!
  return $hooks;
}

function metarec_preprocess_page(&$vars, $hook) {
 
 if ($vars['node']->type == 'blog'){
    $vars['title'] = 'Blog';
  }
}


function metarec_blocks($region, $show_blocks = NULL) {
   
    if (module_exists("context")){
     
      // Since Drupal 6 doesn't pass $show_blocks to theme_blocks, we manually call
      // theme('blocks', NULL, $show_blocks) so that this function can remember the
      // value on later calls.
      static $render_sidebars = TRUE;
      if (!is_null($show_blocks)) {
        $render_sidebars = $show_blocks;
      }
     
        // Bail if this region is disabled.
      $disabled_regions = context_active_values('theme_regiontoggle');
      if (!empty($disabled_regions) && in_array($region, $disabled_regions)) {
        return '';
      }

      // If zen_blocks was called with a NULL region, its likely we were just
      // setting the $render_sidebars static variable.
      if ($region) {
        $output = '';
   
        // If $renders_sidebars is FALSE, don't render any region whose name begins
        // with "sidebar_".
        if (($render_sidebars || (strpos($region, 'sidebar_') !== 0)) && ($list = context_block_list($region))) {
          foreach ($list as $key => $block) {
            // $key == module_delta
            $output .= theme('block', $block);
          }
        }
   
        // Add any content assigned to this region through drupal_set_content() calls.
        $output .= drupal_get_content($region);
   
        $elements['#children'] = $output;
        $elements['#region'] = $region;
   
        return $output ? theme('region', $elements) : '';
      }
     
    }
    else return zen_blocks($region, $show_blocks);
}

function metarec_preprocess_node(&$vars, $hook) {

  $type_preprocess = 'metarec_preprocess_node_type_' . $vars['node']->type;

  if (function_exists($type_preprocess)) {
    $type_preprocess($vars);
  }
}

function metarec_preprocess_node_type_blog(&$vars) {

 // kpr($vars);

  $vars['datetime'] = format_date($vars['node']->created, 'custom', 'G:i');
  $vars['blog_stats_counter'] = $vars['node']->links['statistics_counter']['title'];
  
  // Create blog links
  
  $vars['blog_user'] = l(
    $vars['node']->links['blog_usernames_blog']['title'],
    $vars['node']->links['blog_usernames_blog']['href'],
    array('attributes' => $vars['node']->links['blog_usernames_blog']['attributes'])
  );
  
  $vars['blog_comment_counter'] = l(
    $vars['node']->links['comment_comments']['title'],
    $vars['node']->links['comment_comments']['href'],
    array('attributes' => $vars['node']->links['comment_comments']['attributes'])
  );  
  
  $vars['blog_read_more'] = l(
    $vars['node']->links['node_read_more']['title'],
    $vars['node']->links['node_read_more']['href'],
    array('attributes' => $vars['node']->links['node_read_more']['attributes'])
  );  
  
}



/**
 * Override or insert variables into all templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered (name of the .tpl.php file.)
 */
/* -- Delete this line if you want to use this function
function metarec_preprocess(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */

/**
 * Override or insert variables into the page templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("page" in this case.)
 */
/* -- Delete this line if you want to use this function
function metarec_preprocess_page(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */

/**
 * Override or insert variables into the node templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("node" in this case.)
 */
/* -- Delete this line if you want to use this function
function metarec_preprocess_node(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');

  // Optionally, run node-type-specific preprocess functions, like
  // metarec_preprocess_node_page() or metarec_preprocess_node_story().
  $function = __FUNCTION__ . '_' . $vars['node']->type;
  if (function_exists($function)) {
    $function($vars, $hook);
  }
}
// */

/**
 * Override or insert variables into the comment templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("comment" in this case.)
 */
/* -- Delete this line if you want to use this function
function metarec_preprocess_comment(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */

/**
 * Override or insert variables into the block templates.
 *
 * @param $vars
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered ("block" in this case.)
 */
/* -- Delete this line if you want to use this function
function metarec_preprocess_block(&$vars, $hook) {
  $vars['sample_variable'] = t('Lorem ipsum.');
}
// */
