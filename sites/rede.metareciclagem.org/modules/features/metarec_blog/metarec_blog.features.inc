<?php

/**
 * Implementation of hook_context_default_contexts().
 */
function metarec_blog_context_default_contexts() {
  module_load_include('inc', 'metarec_blog', 'metarec_blog.defaults');
  $args = func_get_args();
  return call_user_func_array('_metarec_blog_context_default_contexts', $args);
}

/**
 * Implementation of hook_views_default_views().
 */
function metarec_blog_views_default_views() {
  module_load_include('inc', 'metarec_blog', 'metarec_blog.features.views');
  $args = func_get_args();
  return call_user_func_array('_metarec_blog_views_default_views', $args);
}
