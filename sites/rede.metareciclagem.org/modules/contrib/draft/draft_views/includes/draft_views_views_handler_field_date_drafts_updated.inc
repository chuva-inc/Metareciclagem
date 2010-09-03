<?php

/**
 * Field handler to present render the date correctly
 */
class draft_views_views_handler_field_date_drafts_updated extends views_handler_field_date {
  // An example of field level access control.
  function access() {
    return user_access('access save as draft');
  }
}

?>