<?php

/**
 * Field handler to present title or body information from the data stored
 */
class draft_views_views_handler_field_draft_data extends views_handler_field {
  function access() {
    return user_access('access save as draft');
  }

  function render($values) {
    $data = unserialize($values->drafts_data);
    if (isset($data['title']) && drupal_strlen($data['title'])) {
      return $data['title'];
    }
    return $data['body'];
  }
}

?>
