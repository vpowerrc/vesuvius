<?
/**
 * @name         Lost Person Finder Theme
 * @version      3.0
 * @package      lpf
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @link         http://sahanafoundation.org
 * @license	 http://www.gnu.org/licenses/lgpl-2.1.html GNU Lesser General Public License (LGPL)
 * @lastModified 2011.0816
 */


$legaleseLink = "OMB NO: 0925-0612 EXPIRATION DATE: 6/30/2013";

$legalese = "Notice: Submission of information is voluntary. All submitted information will be made publicly available. OMB NO: 0925-0612 EXPIRATION DATE: 6/30/2013 Public reporting burden for this collection of information is estimated to average 0.08 hours per response. This estimate includes the time for reviewing instructions, gathering, and entering data. An agency may not conduct or sponsor, and a person is not required to respond to, a collection of information unless it displays a currently valid OMB control number. Send comments regarding this burden estimate or any other aspect of this collection of information, including suggestions for reducing this burden, to: NIH, Project Clearance Branch, 6705 Rockledge Drive, MSC 7974, Bethesda, MD 20892-7974, ATTN: PRA (0925-0612). Do not return the completed form to this address.";

?>

<script>
  var navigation = responsiveNav(".nav-collapse", {
        animate: true,                    // Boolean: Use CSS3 transitions, true or false
        transition: 284,                  // Integer: Speed of the transition, in milliseconds
        label: "Menu",                    // String: Label for the navigation toggle
        insert: "after",                  // String: Insert the toggle before or after the navigation
        customToggle: "",                 // Selector: Specify the ID of a custom toggle
        closeOnNavClick: false,           // Boolean: Close the navigation when one of the links are clicked
        openPos: "relative",              // String: Position of the opened nav, relative or static
        navClass: "nav-collapse",         // String: Default CSS class. If changed, you need to edit the CSS too!
        navActiveClass: "js-nav-active",  // String: Class that is added to <html> element when nav is active
        jsClass: "js",                    // String: 'JS enabled' class which is added to <html> element
        init: function(){},               // Function: Init callback
        open: function(){},               // Function: Open callback
        close: function(){}               // Function: Close callback
      });
</script>

<div id="footer"><center><table id="footerTable">
		<tr>
	
	
		<td>
		<div id="sahana_logo">
			<a href="http://sahanafoundation.org"><img src="theme/responsive
/img/sahanalogo.png" style='width:100%;' border="0" alt="Sahana Software Foundation Logo"></a><br>
		</div>	
		</td>
		</tr>
	</table>
	
	</center>
</div>
<?php


