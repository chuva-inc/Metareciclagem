// $Id: img_assist_fckeditor.js,v 1.1.4.3.2.6 2009/08/02 20:31:21 jorrit Exp $
/**
 * This script loads img_assist_textarea.js and modifies its functionality to
 * work with FCKeditor.
 * 
 * This file does not have to be replaced (in contrast to older versions of this
 * file)
 */
new function() {
  // Step 2: do our own loading
  var initFCKeditor = function() {
    var oldInsertToEditor = insertToEditor;

    insertToEditor = function(content) {
      // handle FCKeditor in popup mode
      if ((myTextarea == '') && (window.opener)) {
        var opener = window.opener;
        if (opener.oFCKeditor) {
          var inst = opener.oFCKeditor.InstanceName;
          var oEditor = opener.FCKeditorAPI.GetInstance(inst);
          if (oEditor.EditMode == opener.FCK_EDITMODE_WYSIWYG) {
            oEditor.InsertHtml(content);
          } else {
            alert(Drupal.t('Inserting image into FCKeditor is allowed only in WYSIWYG mode'));
          }
          cancelAction();
          return false;
        }
      }

      // FCKeditor enabled and running == textarea not displayed
      if (myTextarea.style.display == 'none') {
        var opener = window.opener;
        if (opener.fckLaunchedJsId) {
          for ( var i = 0; i < opener.fckLaunchedJsId.length; i++) {
            if (opener.fckLaunchedTextareaId[i] == myTextarea.id) {
              var oEditor = opener.FCKeditorAPI.GetInstance(opener.fckLaunchedJsId[i]);
              if (oEditor.EditMode == opener.FCK_EDITMODE_WYSIWYG) {
                oEditor.InsertHtml(content);
              } else {
                alert(Drupal.t('Inserting image into FCKeditor is allowed only in WYSIWYG mode'));
              }
            }
          }
        } else {
          var oEditor = opener.FCKeditorAPI.GetInstance(myTextarea.id);
          if (oEditor.EditMode == opener.FCK_EDITMODE_WYSIWYG) {
            oEditor.InsertHtml(content);
          } else {
            alert(Drupal.t('Inserting image into FCKeditor is allowed only in WYSIWYG mode'));
          }
        }
        cancelAction();
        return false;
      }

      oldInsertToEditor(content);
    };
  }

  // Step 1: wait until textarea.js is loaded
  var count = 0;
  var checkAndLoad = function() {
    if (typeof (initLoader) != 'undefined') {
      initFCKeditor();
    } else if (count < 5) {
      setTimeout(checkAndLoad, 1000);
      count++;
    } else {
      alert('Could not load ' + textareafile + ' after 5 seconds');
    }
  }

  checkAndLoad();
}();
