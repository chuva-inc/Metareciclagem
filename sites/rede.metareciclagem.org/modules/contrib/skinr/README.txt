// $Id$

Skinr's main purpose is to allow the theme to define a set of reusable and modular CSS styles, and to make those styles available in Drupal's UI . Skinr was developed for themers to allow them to tap into the power of Drupal's modularity and apply those same principals to theme development. It does not provide any styles of it's own. These styles are defined in the .info file of the theme (or subtheme), by the themer and end up in various places in Drupal's UI, such as:

* Block Configuration
* Node Type (and Comment) Configuration
* [Panel](http://drupal.org/project/panels) Panes
* [Views](http://drupal.org/project/views) Displays

##Basic Syntax

This is the bare minimum that is required in a .info file to create a style.

skinr[system_name][label] = Label Shown in the UI
skinr[system_name][class] = Class(es) output when this style is chosen.

###Some simple examples

; Adds a border-radius to the wrapper element
skinr[rounded][label] = Rounded
skinr[rounded][class] = rounded

; Makes the title big and bold
skinr[big-bold][label] = Big Bold Headers
skinr[big-bold][class] = big-bold

##Advanced Syntax

###Providing Multiple Options

skinr[system_name][1][label] = Label for the first option of a style.
skinr[system_name][1][class] = Class(es) output when this style is chosen.
skinr[system_name][2][label] = Label for the second option of a style.
skinr[system_name][2][class] = Class(es) output when this style is chosen.

Example Use Case: You need to implement 2 designs for menu lists and the structure is mainly the same, but there are 2 different color options.  One way you could do that is:

* Create the structural CSS in .menu-style
* Handle each color option separately in their respective class, as extensions of .menu-style

The Syntax for this example would be:

skinr[menu-style][1][label] = Menu Style: White on Black
skinr[menu-style][1][class] = menu-style menu-white-black
skinr[menu-style][2][label] = Menu Style: Black on White
skinr[menu-style][2][class] = menu-style menu-black-white

###Selectively restricting styles to de-clutter the UI

By default Skinr will assume that your styles can be used anywhere Skinr is available on your site.  If you want to reduce UI clutter and have styles that are only meant to be used in certain places, you can specify specific areas where you want to show them.

skinr[system_name][features][] = block
skinr[system_name][features][] = panel-pane
skinr[system_name][features][] = node
skinr[system_name][features][] = comment
skinr[system_name][features][] = view

Example Use Case: Your style only includes CSS for menus.  You know that Drupal only outputs menus through blocks and panel panes, so you don't want see the style in the Skinr options in Views or Node Types. The syntax for this would be:

skinr[menu-style][features][] = block
skinr[menu-style][features][] = panel-pane

#Making Skinr work with your theme.

In order for Skinr to work, you need to add the $skinr variable to the first <div> in your theme's template files. The variable is the same no matter which type you are dealing with, but you may need to add template files to your theme. The variable is added by doing:

<?php print $skinr; ?>

NOTE: Depending on how your template files are structured, you may need to add a blank space before the variable so it doesn't conflict with other classes you might have:

<?php print ' '. $skinr; ?>

If you are using a theme that takes care of classes during preprocess, you can add $vars['skinr'] there.

##Skinr Default Template Files

* blocks: block.tpl.php
* nodes: node.tpl.php
* comments: comment-wrapper.tpl.php
* views: views-view.tpl.php
* panels: no template file required

NOTE: If you have other template files, make sure you print the $skinr variable in them, otherwise it wont work.

#Stylesheets and Javascript Files

Skinr requires you to create and load your own CSS & JS files.