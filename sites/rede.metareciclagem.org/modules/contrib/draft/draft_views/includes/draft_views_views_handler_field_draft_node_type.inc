<?php

/**
 * Field handler to present render the date correctly
 */
class draft_views_views_handler_field_draft_node_type extends views_handler_field {
  // An example of field level access control.
  function access() {
    return user_access('access save as draft');
  }

  function render($values) {
    $node_types = node_get_types('names');
    if (isset($node_types[$values->drafts_node_type])) {
      return $node_types[$values->drafts_node_type];
    }
    return $values->drafts_node_type;
  }
}

?>