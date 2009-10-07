<?php
// $Id: image_gallery_handler_field_gallery_cover_latest_time.inc,v 1.1 2009/08/27 12:10:57 joachim Exp $

/**
 * Field handler for the gallery's updated time.
 */
class image_gallery_handler_field_gallery_cover_latest_time extends image_gallery_handler_field_gallery_cover {
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Overwrite the descendants option so the text is relevant.
    $form['descendants']['#description'] = theme('advanced_help_topic', 'image_gallery', 'descendants') .
      t('Whether to only consider this gallery itself, or consider subgalleries all together, or recurse into subgalleries if the gallery itself is empty.');
    $form['descendants']['#options'] = array(
      'single'  => t('Only get latest time from this gallery'),
      'flat'    => t('Consider subgalleries, flattened.'),
      'recurse' => t('Consider subgalleries, recursively. (Warning: this can produce many queries per row if your parent galleries are empty!).'),
    );
  }
  
  /**
   * Returns field html.
   */
  function render($values) {
    $nid = $this->get_cover_node_nid($values);

    $latest_node = node_load($nid);
    if ($latest_node->changed) {
      $output = theme('image_gallery_updated', $latest_node->changed);
      return $this->render_link($output, $values);
    }
  }
}
