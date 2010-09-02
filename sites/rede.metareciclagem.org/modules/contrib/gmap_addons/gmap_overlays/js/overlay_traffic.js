/**
 *  The Google Maps Traffic Overlay.
 */
/* $Id: overlay_traffic.js,v 1.2 2008/09/30 20:33:58 bdragon Exp $ */

Drupal.gmap.addHandler('gmap', function(elem) {
  var obj = this;
  obj.bind('init', function() {
    $.each(obj.vars.overlay, function(i,d) {
      switch (d.type) {
        case 'traffic':
          // @@@ Add an overlay interface so all this can be managed?
          obj.map.addOverlay(new GTrafficOverlay());
          break;
      }
    });
  });
});