<?
/**
 * @name         PL User Services
 * @version      2.3
 * @package      plus
 * @author       Greg Miernicki <g@miernicki.com> <gregory.miernicki@nih.gov>
 * @about        Developed in whole or part by the U.S. National Library of Medicine
 * @link         https://pl.nlm.nih.gov/about
 * @license	 http://www.gnu.org/copyleft/lesser.html GNU Lesser General Public License (LGPL)
 * @lastModified 2012.0130
 */


$user = "testDontDelete";
$pass = "dontDelete99";
require_once("../../3rd/nusoap/lib/nusoap.php");

//$wsdl = "https://pl.nlm.nih.gov/?wsdl&api=2.3";
//$wsdl = "https://plstage.nlm.nih.gov/?wsdl&api=2.2";
$wsdl = "http://ceb-stage-lx.nlm.nih.gov/~miernickig/vesuvius/vesuvius/www/index.php?wsdl&api=2.3";
$client = new nusoap_client($wsdl);

//$result = $client->call('getEventListUser', array('username'=>$user, 'password'=>$pass));
//$result = $client->call('getEventList', array(null));
//$result = $client->call('getNullTokenList', array('tokenStart'=>'0', 'tokenEnd'=>'120', 'username'=>$user, 'password'=>$pass));
//$result = $client->call('getImageListBlock', array('tokenStart'=>'314', 'stride'=>2, 'username'=>$user, 'password'=>$pass));
//$result = $client->call('getImageList', array('tokenStart'=>'262', 'tokenEnd'=>'311', 'username'=>$user, 'password'=>$pass));
//$result = $client->call('getImageCountsAndTokens', array('username'=>$user, 'password'=>$pass));
//$result = $client->call('expirePerson', array('uuid'=>'pl.nlm.nih.gov/person.4001018', 'explanation'=>'because!!!!', 'username'=>$user, 'password'=>$pass));
//$result = $client->call('setPersonExpiryDate', array('uuid'=>'pl.nlm.nih.gov/person.4001018', 'expiryDate'=>'2011-01-01 01:23:46', 'username'=>$user, 'password'=>$pass));
//$result = $client->call('setPersonExpiryDateOneYear', array('uuid'=>'pl.nlm.nih.gov/person.4001018', 'username'=>$user, 'password'=>$pass));
//$result = $client->call('changeMassCasualtyId', array('newMcid'=>'XXX', 'uuid'=>'3', 'username'=>$user, 'password'=>$pass));
//$result = $client->call('getUuidByMassCasualtyId', array('mcid'=>'91140', 'shortname'=>'test', 'username'=>$user, 'password'=>$pass));
//$result = $client->call('getPersonExpiryDate', array('uuid'=>'pl.nlm.nih.gov/person.4000579'));
//$result = $client->call('hasRecordBeenRevised', array('uuid'=>'pl.nlm.nih.gov/person.4000579', 'username'=>$user, 'password'=>$pass));
//$result = $client->call('checkUserAuth', array('username'=>$user, 'password'=>$pass));
//$result = $client->call('getHospitalPolicy', array('hospital_uuid'=>1));
//$result = $client->call('getHospitalLegaleseTimestamps', array('hospital_uuid'=>1));
//$result = $client->call('registerUser', array('username'=>'testCaseUser', 'emailAddress'=>'testCase@email.com', 'password'=>'testPassword99', 'givenName'=>'testCaseGiven', 'familyName'=>'testCaseFamily'));
//$result = $client->call('changeUserPassword', array('username'=>$user, 'oldPassword'=>$pass, 'newPassword'=>$pass));
//$result = $client->call('resetUserPassword', array('email'=>"pl@tehk.org"));
//$result = $client->call('forgotUsername', array('email'=>"testCase@email.com"));
//$result = $client->call('reportPerson', array('personXML'=>null, 'eventShortName'=>null, 'xmlFormat'=>'TRIAGEPIC', 'username'=>null, 'password'=>null));
//$result = $client->call('createPersonUuid', array('username'=>'testDontDelete', 'password'=>'dontDelete99'));
//$result = $client->call('createPersonUuidBatch', array('number'=>5, 'username'=>'testDontDelete', 'password'=>'dontDelete99'));

/*
$result = $client->call('searchCountWithAuth', array(
	'eventShortname'=>'test',
	'searchTerm'=>'',
	'filterStatusMissing'=>true,
	'filterStatusAlive'=>true,
	'filterStatusInjured'=>true,
	'filterStatusDeceased'=>true,
	'filterStatusUnknown'=>true,
	'filterStatusFound'=>true,
	'filterGenderComplex'=>true,
	'filterGenderMale'=>true,
	'filterGenderFemale'=>true,
	'filterGenderUnknown'=>true,
	'filterAgeChild'=>true,
	'filterAgeAdult'=>true,
	'filterAgeUnknown'=>true,
	'filterHospitalSH'=>true,
	'filterHospitalWRNMMC'=>true,
	'filterHospitalOther'=>true,
	'pageStart'=>0,
	'perPage'=>2,
	'sortBy'=>'',
	'username'=>$user,
	'password'=>$pass
));
*/

//$x = file_get_contents("RU.xml");
$x = file_get_contents("reference_REUNITE3.xml");
//$result = $client->call('reportPerson', array('personXML'=>$x, 'eventShortName'=>'test', 'xmlFormat'=>'REUNITE3', 'username'=>$user, 'password'=>$pass));
//$result = $client->call('reReportPerson', array('uuid'=>'pl.nlm.nih.gov/person.2970291', 'personXML'=>$x, 'eventShortName'=>'test', 'xmlFormat'=>'REUNITE3', 'username'=>$user, 'password'=>$pass));

$x = file_get_contents("testTP1.xml");
//$x = file_get_contents("reference_TRIAGEPIC1.xml");
$result = $client->call('reportPerson', array('personXML'=>$x, 'eventShortName'=>'test', 'xmlFormat'=>'TRIAGEPIC1', 'username'=>$user, 'password'=>$pass));
//$result = $client->call('reReportPerson', array('uuid'=>'pl.nlm.nih.gov/person.2970291', 'personXML'=>$x, 'eventShortName'=>'test', 'xmlFormat'=>'TRIAGEPIC1', 'username'=>$user, 'password'=>$pass));

echo "<pre>wsdl >> ".$wsdl."\n\n".var_export($result, true)."</pre>";


//echo "<pre>eventList: ".print_r(json_decode($result['resultSet']), true)."</pre>";







