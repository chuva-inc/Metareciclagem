// $Id: iconizer.admin.js,v 1.1.2.2 2010/11/26 13:39:26 thepanz Exp $
$(document).ready(function(){
  $('#edit-iconizer-files-icons').click(iconizer_visibility_togle);
  
  iconizer_visibility_togle();
  
  function iconizer_visibility_togle(){
    if ($('#edit-iconizer-files-icons:checked').val() == 1) {
      // Show the other controls
      // alert("show");
      $('.iconizer_file_icons_visibility').show();
    }
    else {
      // alert("hide");
      $('.iconizer_file_icons_visibility').hide();
    }
    return true;
  }
});