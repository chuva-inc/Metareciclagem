<?php

/**
 * Field handler to display a view link
 */
class draft_views_views_handler_field_draft_view extends views_handler_field {
  // An example of field level access control
  function access() {
    return user_access('access save as draft');
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields(array('drafts_node_type' => 'node_type'));
  }

  function render($values) {
    $data = unserialize(db_result(db_query("SELECT data FROM {drafts} WHERE draft_id = %d", $values->drafts_draft_id)));
    if (isset($data['node_id_from_server']) && is_numeric($data['node_id_from_server'])) {
      $output = l(t('View'), 'node/'. $data['node_id_from_server'] .'/edit', array('query' => array('draft_id' => $values->drafts_draft_id)));
    }
    else {
      $output = l(t('View'), 'node/add/'. str_replace("_", "-", $values->drafts_node_type), array('query' => array('draft_id' => $values->drafts_draft_id)));
    }
    $output .= ' | ';
    $output .= l(t('Delete'), 'draft/remove/'.$values->drafts_draft_id);
    return $output;
  }
}

?>
