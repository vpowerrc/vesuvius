
<?php
include_once ($global['approot'] . '/inc/lib_image.inc');
/**
 * Home Page
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @author	   Isuru Samaraweera(isuru@opensource.lk) 
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @package    module
 * @subpackage dvr
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 *
 */
 ?>
<div id="home">
<h2><?= _('Disaster Victim Registry'); ?></h2>
<p>
<?php

	print _("The SAHANA Disaster Victim Registry is a central online repository " .
	"where information on all the disaster victims can be stored.Information like name,age" .
	",contact number,id card number,religion,race,displaced location,current location and other " .
	"physical details are captured.Also victims picture and finger print details can be uploaded to" .
	"the system .Also the groupwise information is captured.This module can be used by" .
	" any NGO/organization prior or after to a disaster"  );
?>

</p>

<strong>Features include:</strong>
<ul>
    <li>
    <?php

	print _("Capture Information on Disaster Victim groups(Toursists,Passengers" .
			",Families,etc..)")
?>
    </li>
    <li>
    <?php print _("Capture Information on each disaster victim") ?>
    </li>
    <li>
    <?php print _("Picture upload and finger print upload facility")?>
    </li>
    <li>
    <?php print _("Searching for different groups and individuals") ?>
    </li>
    <li>
    <?php print _("Modify Information on groups and individuals") ?>
    </li>
    <li>
    <?php print _("Various Reporting functionalities") ?>
    </li>
   <!-- <li>
    <?php print _("Forecasting methods based on statistics") ?>
   
    </li>-->
</ul>
<br/>
</div>

<div id="home_recent">



<h1><?= _('Latest updates on Reported  Victims'); ?></h1>
<?php

shn_dvr_home_show_dvr();
?>
</div>

<?php




function shn_dvr_home_show_dvr()
{
    global $global; 

   
    $sql= "SELECT distinct a.p_uuid AS p_uuid, a.full_name AS full_name FROM person_uuid a ,image im where im.x_uuid=a.p_uuid order by im.created ";
            

           $rs = $global['db']->SelectLimit($sql,6);
   
    if($rs){
        $arr = $rs->GetAll();
   
        shn_dvr_search_show_verticle($arr);
    }
}









function shn_dvr_search_show_verticle($details)
{
    global $global;
    global $conf;
?>
<DIV ID="result">
<TABLE>
<?
    for($i=0; $i<count($details); $i+=2){
        if($details[$i]){
?>
    <TR>
        <TD>
<?php
          shn_show_thumb_url($details[$i]['p_uuid'],'database','dvr','addvictim_img',false);
	        echo '<br /><a href="index.php?mod='.$global['module'].'&act=editp&id='.$details[$i]['p_uuid'].'">'.$details[$i]['full_name'].'</a><br />';
	      
	      
   
?>
        </TD>
<?php
            if($details[$i+1]){
?>
        <TD>
<?php
shn_show_thumb_url($details[$i+1]['p_uuid'],'database','dvr','addvictim_img',false);
               
	                echo '<br /><a href="index.php?mod='.$global['module'].'&act=editmp&id='.$details[$i+1]['p_uuid'].'">'.$details[$i+1]['full_name'].'</a><br />';
		            
		        } 
              //  echo '<br /><a href="index.php?mod=admin&act=ims_assign&id='.$details[$i]['p_uuid'] .'">'._('Assign to more incidents').'</a>';
?>
        </TD>
<?php
            }
?>
    </TR>
<?php
        }
    }
?>
</TABLE>
</DIV>
