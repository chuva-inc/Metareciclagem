// $id Javascript portion for the Draft Module

if ($.browser.msie === true && $.browser.version == 6.0) {
  window.onscroll = function() {
    $('.draft_save').css('top', document.documentElement.scrollTop + 'px');
  };
}

/**
 * Creating our namespace for the module so we do not conflict
 * with any other modules that will utilize the same function names
 */
Drupal.draft = {};

if (Drupal.jsEnabled) {
  $(document).ready(function() {
    var str = '<div id="draft_save" class="draft_save">' +
              '<div class="title">' + Drupal.t("Processing....") + '</div>' +
              '</div>';
    $('body').append(str);
  });
}

/**
 * Function for setting the timeout to save the draft information
 */
Drupal.draft.saveTimeout = function() {
  setTimeout(Drupal.draft.saveForm, Drupal.settings.draft.interval);
}

/**
 * Function to save the form
 */
Drupal.draft.saveForm = function() {
  $('#' + Drupal.settings.draft.button_id).attr('disabled', 'disabled');
  $('.draft_save .title').html(Drupal.t('Draft is being saved...')).parent().slideDown();

  // Triggering the tinyMCE save piece so it will give us the text into the body portion
  if (typeof tinyMCE == 'object') {
    tinyMCE.triggerSave();
  }
  // adding FCKEditor support
  if (typeof FCKeditorAPI == 'object' && typeof FCKeditorAPI.Instances != 'undefined') {
    for (var obj in FCKeditorAPI.Instances) {
      var fck = FCKeditorAPI.GetInstance(obj);
      if (fck) {
        fck.UpdateLinkedField();
      }
    }
  }
  // adding CKEditor support
  if (typeof CKEDITOR != 'undefined' && typeof CKEDITOR.instances != 'undefined') {
    for (var obj in CKEDITOR.instances) {
      var ck = CKEDITOR.instances[obj];
      if (ck) {
        ck.setData($('#' + obj).val());
      }
    }
  }

  // utilizing the jquery.fields.js plugin here for form hash
  var form_data = $('#' + Drupal.settings.draft.form_id).formHash();
  // removing the tokens we specified in the configuration of the module
  var tokens = Drupal.settings.draft['form_elements_ignore'].split('|');
  for (var x = 0; x < tokens.length; x++) {
    var token = tokens[x];
    if (typeof form_data[token] != 'undefined') {
      delete form_data[token];
    }
  }
  // Setting the node type based off the information in our settings
  form_data['node_type'] = Drupal.settings.draft.node_type;
  // Checking if it was an edit node and if so return the node id also
  if (typeof Drupal.settings.draft.node_id != 'undefined') {
    form_data['node_id_from_server'] = Drupal.settings.draft.node_id;
  }

  // this is so the form select box data will be stored correctly
  var saved;
  for (key in form_data) {
    saved = form_data[key];
    delete form_data[key];
    key = key.replace(/\[/g,'(').replace(/\]/g,')')
    form_data[key] = saved;
  }

  // sending the data back to the server for saving the draft format
  $.ajax({
    url: Drupal.settings.draft.url,
    type: "POST",
    dataType: "xml/html/script/json",
    data: form_data,
    success: function(draft_id, str) {
      $('#edit-draft-id').val(parseInt(draft_id));
      $('.draft_save .title').html(Drupal.t('Draft with Draft ID ' + draft_id + ' has been saved successfully'));
    },
    complete: function() {
      $('#' + Drupal.settings.draft.button_id).removeAttr('disabled');
      setTimeout(function() { $('.draft_save').slideUp(); }, 3000);
    }
  });
  // Only re-call the function if autosave has been enabled
  if (Drupal.settings.draft.autosave === 1) {
    Drupal.draft.saveTimeout();
  }
  return false;
}

/**
 * Function re-populates the form with the information
 */
Drupal.draft.populateForm = function() {
  // Check was added since if the user clicks preview we do not want the
  // Draft to re-populate the form since the user might have changed information
  // Safest thing to do for the module is to not try and populate anything
  if (typeof Drupal.settings.draft.draft_populate_trigger != 'undefined') {
    $('.draft_save').slideUp();
    return false;
  }

  // This is so the select box data will be correctly displayed
  for (key in Drupal.settings.draft.form_data) {
    saved = Drupal.settings.draft.form_data[key];
    delete Drupal.settings.draft.form_data[key];
    key = key.replace(/\(/g,'[').replace(/\)/g,']')
    Drupal.settings.draft.form_data[key] = saved;
  }

  $('#' + Drupal.settings.draft.form_id).formHash(Drupal.settings.draft.form_data);
  // for tinyMCE editor
  if (typeof tinyMCE == 'object') {
    setTimeout(function() {
      for (var obj in tinyMCE.editors) {
        var editor = tinyMCE.editors[obj];
        var text = $('#' + Drupal.settings.draft.form_id + ' #' + obj).val();
        if (text) {
          editor.setContent(text);
        }
      }
      $('.draft_save').slideUp();
    }, 3000);
  };

  // adding FCKEditor support
  if (typeof FCKeditorAPI == 'object' && typeof FCKeditorAPI.Instances != 'undefined') {
    setTimeout(function() {
      for (var obj in FCKeditorAPI.Instances) {
        var fck = FCKeditorAPI.GetInstance(obj);
        if (fck) {
          fck.SetHTML($('#' + fck.Config.TextareaID).val());
        }
      }
      $('.draft_save').slideUp();
    }, 3000);
  }
  // adding CKEditor support
  if (typeof CKEDITOR != 'undefined' && typeof CKEDITOR.instances != 'undefined') {
    setTimeout(function() {
      for (var obj in CKEDITOR.instances) {
        var ck = CKEDITOR.instances[obj];
        if (ck) {
          ck.updateElement();
        }
      }
    }, 3000);
  }
  // We only hide processing if FCK, CK or TinyMCE objects do not exist in the system
  if (typeof FCKeditorAPI == 'undefined' && typeof tinyMCE == 'undefined' && typeof CKEDITOR == 'undefined') {
    $('.draft_save').slideUp();
  }
}
