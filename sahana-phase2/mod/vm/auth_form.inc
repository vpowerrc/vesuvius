<?PHP
/**
 *
 * Sahana authentication form generator library.
 * 
 *
 * PHP version 4 and 5
 *
 * LICENSE: This source file is subject to LGPL license
 * that is available through the world-wide-web at the following URI:
 * http://www.gnu.org/copyleft/lesser.html
 *
 * @package    framework
 * @subpackage security
 * @author     Ravindra De Silva <ravindra@opensource.lk><ravidesilva@iee.org>
 * @copyright  Lanka Software Foundation - http://www.opensource.lk
 * @license    http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * 
 */


	global $global;
    include_once $global['approot']. 'inc/lib_security/authenticate.inc';
    include_once $global['approot']."/inc/lib_errors.inc";
    include_once $global['approot']."/inc/lib_validate.inc";
//    include_once "acl_form_lib.inc";
    include_once $global['approot']."/inc/lib_security/acl_form_lib.inc";
    include_once $global['approot']."/mod/vm/utility_functions.inc";
    include_once $global['approot']."/mod/vm/errors.inc";
   
/**
 * Generates a form to delete a user
 * @return void
 * @access public
 */
function shn_auth_form_user_del($error=false)
{
   
?>
<center><h2>Remove User</h2></center>

<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=admin&act=del_user_cr','id'=>'formset');
	shn_form_open($header,false);
$user=shn_acl_form_users();
$acl_users = array();
array_push(
		$acl_users,
		$user
	  );

    shn_form_add_component_list($acl_users,$section=true,$legend='',$return=false,$default_val_req=true);
?>
</br>
<center>
<?php
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Remove Users');
	shn_form_add_component($submit,false,false);
?>
</center>
</br>
<?php
        //close the form
     	shn_form_close(false);
}

function _shn_admin_del_user_cr(){
   global $global;
$user=$_POST{"users"};
 $db=$global["db"];
$VARCHAR=100;
for($i=0;$i<count($user);$i++){
      $q="delete from org_users where user_id=$user[$i]";
                $res=$db->Execute($q);
$q="delete from users where p_uuid=$user[$i]";
                $res=$db->Execute($q);
}
shn_admin_del_user(false);

}

/**
 * Generates a form to add an user
 * @return void
 * @access public
 */

function shn_auth_form_user_add($title="Add an User",$header=null,$error=false, $uuid)
{
//dbgpost($_POST);
?>
<center><h2><? echo $title ?></h2></center>
<h3>Fields marked with * are required (entry is compulsory)</h3>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
if($header==NULL){
   	$header=array('method'=>'POST','action'=>'index.php?mod=admin&act=add_user_cr','id'=>'formset');
}
	shn_form_open($header,false);
	?><input type="hidden" name="uuid" value="<?php echo $uuid?>"><?php
//	$org=shn_user_orgs();                  // RAM 7/2006 eliminating the organization field from the form
//	$or_arr=array();
//	array_push(
//		$or_arr,
//		$org
//	);
//	shn_form_add_component_list($or_arr,$section=true,$legend='Add a User for the Organization',$return=false,$default_val_req=false);

    $login_info = array(    
	    array('desc'=>_("Account Name : "),'type'=>"text",'size'=>20,'name'=>'account_name','br'=>1, 
		  'value'=>null, 'caption_align'=>null, 'section_start'=>null, 'section_end'=>null),         // RAM 7/2006 Added these extra entries
	    array('desc'=>_("* User Name for Login: "),'type'=>"text",'size'=>20,'name'=>'user_name','br'=>1,
		  'value'=>null, 'caption_align'=>null, 'section_start'=>null, 'section_end'=>null),       // RAM 7/2006 Added these extra entries
	    array('desc'=>_("* Password for Login: "),'type'=>"password",'size'=>20,'name'=>'password','br'=>1,
		  'value'=>null, 'caption_align'=>null, 'section_start'=>null, 'section_end'=>null),       // RAM 7/2006 Added these extra entries
	    array('desc'=>_("* Confirm Password: "),'type'=>"password",'size'=>20,'name'=>'re_password','br'=>1,
		  'value'=>null, 'caption_align'=>null, 'section_start'=>null, 'section_end'=>null),       // RAM 7/2006 Added these extra entries
    ); // end of getting logging info
    shn_form_add_component_list($login_info,$section=true,$legend='Create an Account for Login',$return=false,$default_val_req=false);
?>
</br>
<center>
<?php
//create the submit button
//    $submit= array('type'=>'submit', 'value'=>'Submit');
    $submit= array('type'=>'submit', 'value'=>'Submit', 'desc'=>null, 'caption_align'=>null, 'br'=>null);
    //	$output .= shn_form_add_component($submit,$return=false,false);
    //	echo $output;
    shn_form_add_component($submit,$return=false,false);
?>
</center>
</br>
<?php
        //close the form
     	shn_form_close(false);
?>				     
</div>
<?php
    // end of form

    
} 


function _shn_admin_add_user_cr(){
   global $global;
 	$db=$global["db"];
	$VARCHAR=100;
   list($error,$user_name)=(shn_validate_user_name($_POST{"user_name"}))?array($error,$_POST{"user_name"}):array(true,NULL);
    
    //for the moment return true
    list($error,$password)=(shn_validate_password($_POST{"password"}))?array($error,$_POST{"password"}):array(true,NULL);
    if (is_null($_POST{"re_password"})){
        $error=true;
        add_error(SHN_ERR_OR_REPWD_INCOMPLETE);
    }else {    
        $re_password=trim($_POST{"re_password"});
    }
    if (!($password==$re_password)){
        $error=true;
        add_error(SHN_ERR_OR_REPWD_WRONG);
    }
	 if (trim(strlen($_POST{"account_name"})) > $VARCHAR){
        $error=true;
        add_error(SHN_ERR_OR_REG_MAX);
    }else {
        $account_name=$_POST{"account_name"};
    }
    if (is_null($_POST{"org"})){
        $error=true;
        add_error(SHN_ERR_OR_INCOMPLETE);
    }else {    
        $org_id=trim($_POST{"org"});
    }
	$pid=shn_add_user($account_name,$user_name,$password,"user",-1);
    $q="insert into org_users(org_id,user_id) values($org_id,$pid)";
    $res=$db->Execute($q);
    return $error;
}

/**
 * Generates a form to change the password
 * @return void
 * @access public
 */
 
function shn_auth_form_ch_pwd($error=false)
{


?>
<center><h2>Change Password</h2></center>
<h3>Fields marked with * are required (entry is compulsory)</h3>
<?php
    if($error)
    display_errors();
?>               
<div id="formcontainer">
<?php
   	$header=array('method'=>'POST','action'=>'index.php?mod=vm&act=ch_pwd_cr','id'=>'formset');
	shn_form_open($header,false);
$login_info = array(    
			
                //    array('desc'=>_("* User Name for Login: "),'type'=>"text",'size'=>20,'name'=>'user_name','br'=>1),
array('desc'=>_("* Old Password: "),'type'=>"password",'size'=>20,'name'=>'old_password','br'=>1),
                    array('desc'=>_("* New Password: "),'type'=>"password",'size'=>20,'name'=>'password','br'=>1),
                    array('desc'=>_("* Confirm New Password: "),'type'=>"password",'size'=>20,'name'=>'re_password','br'=>1)
    ); // end of getting logging info
    shn_form_add_component_list($login_info,$section=true,$legend='Create an Account for Login',$return=false,$default_val_req=false);
$user_id=$_SESSION["user_id"];
$user=array('type'=>"hidden",'name'=>'user','value'=>$user_id); 
shn_form_add_component($user,$return=false,$default_val_req=false);
?>
</br>
<center>
<?php
//create the submit button
    $submit= array('type'=>'submit', 'value'=>'Submit');
	shn_form_add_component($submit,false,false);
?>
</center>
</br>
<?php
        //close the form
     	shn_form_close(false);
?>				     
</div>
<?php
    // end of form

    
} 

function _shn_admin_ch_pwd_cr(){
    global $global;
    $db=$global["db"];
    $VARCHAR=100;
    
    //for the moment return true
    list($error,$password)=(shn_validate_password($_POST{"password"}))?array($error,$_POST{"password"}):array(true,NULL);
    if (is_null($_POST{"re_password"})){
        $error=true;
        add_error(SHN_ERR_OR_REPWD_INCOMPLETE);
    }else {    
        $re_password=trim($_POST{"re_password"});
    }
    if (!($password==$re_password)){
        $error=true;
        add_error(SHN_ERR_OR_REPWD_WRONG);
    }
        $old_password=trim($_POST{"old_password"});
        $user_id=trim($_POST{"user"});
    $error=shn_change_password($user_id,$old_password,$password);
    shn_auth_form_ch_pwd($error);
}