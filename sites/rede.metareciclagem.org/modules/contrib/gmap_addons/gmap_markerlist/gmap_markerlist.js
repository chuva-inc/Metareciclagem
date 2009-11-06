/* $Id: gmap_markerlist.js,v 1.1 2009/02/26 22:42:48 bdragon Exp $ */

(function () {
  var MarkerList = function (gmap) {
    this.obj = gmap;
  }
  MarkerList.prototype = new GControl();
  MarkerList.prototype.initialize = function (map) {
    this.map = map;
    this.markerlist = document.createElement("div");
    map.getContainer().appendChild(this.markerlist);
    $(this.markerlist).addClass('gmap_markerlist').append('<ul></ul>');
    return this.markerlist;
  }
  MarkerList.prototype.test = function (str) {
    $(this.markerlist).append(str);
  }
  MarkerList.prototype.addMarker = function (marker) {
    var obj = this.obj;
    $('<li>' + marker.opts.title + '</li>').appendTo($('ul', this.markerlist)).click(function () {
      obj.change('clickmarker', -1, marker);
    });
  }
  MarkerList.prototype.getDefaultPosition = function () {
    return new GControlPosition(G_ANCHOR_TOP_RIGHT, new GSize(7, 33));
  }

  Drupal.gmap.addHandler('gmap', function(elem) {
    var obj = this;
    var myList;
    obj.bind('init', function () {
      myList = new MarkerList(obj);
      obj.map.addControl(myList);
    });

    obj.bind('addmarker', function (marker) {
      myList.addMarker(marker);
    });

  });




})();
