<?php
    #         ____
    #        / __/________  ___        ____ _____ _   __
    #       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
    #      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ /
    #     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
    #                               /____/
    #
    #  This file is part of 'Free-gov' - free-gov-core/core.inc
    #
    #  Free-gov - e-government free software system
    #  Copyright (C) 2011 Iris Montes de Oca <http://www.irismontesdeoca.com>
    #  Copyright (C) 2011 Eduardo Glez <http://www.eduardoglez.com>
    #
    #  Free-gov is free software; you can redistribute it and/or modify
    #  it under the terms of the GNU Affero General Public License as published
    #  by the Free Software Foundation; either version 3 of the License, or
    #  (at your option) any later version.
    #
    #  Free-gov is distributed in the hope that it will be useful,
    #  but WITHOUT ANY WARRANTY; without even the implied warranty of
    #  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    #  GNU Affero General Public License for more details.
    #
    #  You should have received a copy of the GNU Affero General Public License
    #  along with Free-gov: see the file 'license.txt'.  If not, write to
    #  the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    #  Boston, MA 02111-1307, USA.
    #
    #   Authors: Iris Montes de Oca <http://www.irismontesdeoca.com>
    #            Eduardo Glez <http://www.eduardoglez.com>
    #  Internet: http://free-gov.org
    #
    #  Registered in the United States Copyright Office on May 18, 2011
    #  Registration Number at the Library of the Congress of the USA: TXu001756584
    #


    //////////////////////////////////////////////////////////////////////////
    // LOAD MAIN CONFIGURATION FILE
    //////////////////////////////////////////////////////////////////////////
    include (CORE_PATH . '/.configuration'); // Set file permissions to 500


    //////////////////////////////////////////////////////////////////////////
    // DATABASE CONNECTION AND FUNCTIONS SECTION
    //////////////////////////////////////////////////////////////////////////

    // Main Database connection. Mysqli handler becomes available at $_FG['db0']
    $_FG['db0'] = mysqli_connect(SQL_DB_HOST, SQL_DB_USER, SQL_DB_PASSWORD, SQL_DB_NAME);
    if (!$_FG['db0']) {
        FG_error('Error connectando a base de datos ( Code: ' . mysqli_connect_errno() . ' )<br>[db.inc]');
    }

    // Browser detection
    //////////////////////////////////////////////////////////////////////////
/*
    if (isset($_SERVER['HTTP_USER_AGENT']) && (strpos($_SERVER['HTTP_USER_AGENT'], 'MSIE') !== FALSE)) {
    header ('Location: /badbrowser');

    $fgbf = $_FG['render']['footer'];
    $_FG['render']['footer'] = '<span class="txtalert">ALERTA: su navegador (Internet Explorer) implica problemas de seguridad. Procure usar este Sistema desde un navegador seguro...<br><br></span>' . $fgbf;
    }
*/

    // Obtain Name from ID on Key-Value tables
    //////////////////////////////////////////////////////////////////////////
    function FG_id2name ($table, $id, $dbhandler = 'db0') {
        global $_FG;
        $result = mysqli_query($_FG[$dbhandler], "SELECT * FROM `$table` WHERE id='$id' LIMIT 0,1");
        if (mysqli_num_rows($result) < 1) {
            return FALSE;
        }
        $buf = mysqli_fetch_assoc($result);
        mysqli_free_result($result);
         return $buf['name'];
    }

    // Obtain ID from Name on Key-Value tables
    //////////////////////////////////////////////////////////////////////////
    function FG_name2id ($table, $name, $dbhandler = 'db0') {
        global $_FG;
        $result = mysqli_query($_FG[$dbhandler], "SELECT * FROM `$table` WHERE name='$name' LIMIT 0,1");
        if (mysqli_num_rows($result) < 1) {
            return FALSE;
        }
        $buf = mysqli_fetch_assoc($result);
        mysqli_free_result($result);
         return $buf['id'];
    }

    // Populate an HTML "select" from a given SQL Key-Value table
    //////////////////////////////////////////////////////////////////////////
    function FG_mkselect ($table, $selected = 1, $order = 'ASC', $dbhandler = 'db0') {
        global $_FG;
        $result = mysqli_query($_FG[$dbhandler], "SELECT * FROM `$table` ORDER BY id $order");
        if (mysqli_num_rows($result) < 1) return FALSE;
        while ($row = mysqli_fetch_assoc($result)) {
            if ($row['id']==$selected) $text .= "<option value=\"{$row['id']}\" selected>{$row['name']}</option>\n";
            else $text .= "<option value=\"{$row['id']}\">{$row['name']}</option>\n";
        }
        mysqli_free_result($result);
         return $text;
    }




    // Date format conversions
    //////////////////////////////////////////////////////////////////////////
    function FG_formatdate2db (&$data, $datefields) {

          if ((!is_array($datefields))||(count($datefields)<1)||(!is_array($data))||(count($data)<1)) return;


          foreach ($datefields as $datefieldname){
              $date1 = strtr ($data[$datefieldname], '/', '-');
              $explodeddate = explode ('-', $date1);
              if (($explodeddate[0]<1)||($explodeddate[1]<1)||($explodeddate[2]<1)) return NULL;
              if (strlen($explodeddate[2])<4) { $date1 = $explodeddate[0] . '-' . $explodeddate[1] . '-20' . $explodeddate[2];  }
              $data[$datefieldname] = date('Y-m-d', strtotime($date1));
            }
    }

    //////////////////////////////////////////////////////////////////////////
    function FG_formatdb2date (&$data, $datefields) { 

          if ((!is_array($datefields))||(count($datefields)<1)||(!is_array($data))||(count($data)<1)) return;
          foreach ($datefields as $datefieldname){

              $explodeddate = array(); $explodeddate = explode ('-', $data[$datefieldname]);  if (  $explodeddate[0]<1  ) { $data[$datefieldname] = NULL; continue; }
              $data[$datefieldname] =   date(SQL_DATE_FORMAT_LONG, strtotime($data[$datefieldname]));  
            }
    }





    // Insert array data in SQL table, despite order
    //////////////////////////////////////////////////////////////////////////
    function FG_dbinsert ($table, $data, $skipid = TRUE, $dbhandler = 'db0') {
        global $_FG;

        if (isset($_FG['datefields']))  {  FG_formatdate2db ($data, $_FG['datefields']); }

        $result = mysqli_query($_FG[$dbhandler], 'SHOW FULL COLUMNS FROM ' . $table);
        if (mysqli_num_rows($result) < 1) return FALSE;
        $comma = '';
        while ($row = mysqli_fetch_assoc($result)) {
            if ($skipid && $row['Field'] == 'id') continue;
            if (!isset($data[$row['Field']])) continue;
            $fieldslist .= $comma . $row['Field'];

            if (strpos($row['Type'], 'int(') !== FALSE) $quote = '';
             else $quote = "'";
            if (!is_array($data[$row['Field']])) {   if(strlen($data[$row['Field']])<1) $quote = "'";    $valueslist .= $comma . $quote . $data[$row['Field']] . $quote; }

             else {
                foreach ($data[$row['Field']] as $element) { $elements .= $element; }  
                $valueslist .= $comma . $quote . $elements . $quote;
                }
            $comma = ', ';
        }

//return 'INSERT INTO `' . $table .'` (' . $fieldslist . ') VALUES (' . $valueslist . ');';

        $result = mysqli_query($_FG[$dbhandler], 'INSERT INTO `' . $table .'` (' . $fieldslist . ') VALUES (' . $valueslist . ');');
        if (mysqli_affected_rows($_FG[$dbhandler]) < 1) return FALSE;
        return mysqli_insert_id($_FG[$dbhandler]);
    }


    // Update data in SQL table on a given id record, despite provided data order
    //////////////////////////////////////////////////////////////////////////
    function FG_dbupdate ($table, $data, $dbhandler = 'db0') {
        global $_FG;

        if (isset($_FG['datefields']))  {  FG_formatdate2db ($data, $_FG['datefields']); }

        //id of register to be updated comes in field 'updatefield' in data array
        $result = mysqli_query($_FG[$dbhandler], 'SHOW FULL COLUMNS FROM ' . $table);
        if (mysqli_num_rows($result) < 1) return FALSE;
        $comma = '';
        while ($row = mysqli_fetch_assoc($result)) {
            if ($row['Field'] == 'id') continue;
            if (!isset($data[$row['Field']])) continue; // field not received
            if ( (strpos($row['Type'], 'int(') !== FALSE) && ((strlen($data[$row['Field']])<1) || (!is_numeric($data[$row['Field']])) ) ) continue; // empty int field received

            if (strpos($row['Type'], 'int(') !== FALSE) $quote = '';
             else $quote = "'";
            if (!is_array($data[$row['Field']])) $value = $quote . $data[$row['Field']] . $quote;
             else {
                foreach ($data[$row['Field']] as $element) $elements .= $element;  
                $value =  $quote . $elements . $quote;
                }
            $valueslist .= $comma . ' `' . $row['Field'] . '`=' . $value ;
            $comma = ', ';
        }

//$encoded = FG_encode ('UPDATE `' . $table . '` SET ' . $valueslist . ' WHERE `id`=' . FG_decode($data['updatefield']) . ' LIMIT 1');
//FG_log('DEBUG', $encoded);

        $updatefield = FG_decode($data['updatefield']);
        $result = mysqli_query($_FG[$dbhandler], 'UPDATE `' . $table . '` SET ' . $valueslist . ' WHERE `id`=' . $updatefield . ' LIMIT 1');
       // if (mysqli_affected_rows($_FG[$dbhandler]) < 1) return FALSE;
        return $updatefield;
    }
 


    // Get an array with a register (with a given id) from SQL table
    //////////////////////////////////////////////////////////////////////////
    function FG_dbget ($table, $id, $dbhandler = 'db0') {
        global $_FG;
        $result = mysqli_query($_FG[$dbhandler], 'SELECT * FROM ' . $table . ' WHERE `id`=' . $id . ' LIMIT 1');
        if (mysqli_num_rows($result) < 1) return FALSE;
        
        $row = mysqli_fetch_array($result, MYSQLI_ASSOC);
        if (!is_array($row)) return FALSE;
        return $row;
    }



    // Get an array with a register (with a given field + value) from SQL table
    //////////////////////////////////////////////////////////////////////////
    function FG_dbgetbyfield ($table, $field, $value, $dbhandler = 'db0') {
        global $_FG;
        if (!is_numeric($value)) $value = "'$value'"; 
        $result = mysqli_query($_FG[$dbhandler], 'SELECT * FROM ' . $table . ' WHERE `' . $field . '`=' . $value . ' LIMIT 1');
        if (mysqli_num_rows($result) < 1) return FALSE;
        
        $row = mysqli_fetch_array($result, MYSQLI_ASSOC);
        if (!is_array($row)) return FALSE;
        return $row;
    }


    // Delete 'id' identified register from SQL table
    //////////////////////////////////////////////////////////////////////////
    function FG_dbdelete ($table, $id, $dbhandler = 'db0') {
        global $_FG;
        if (!is_numeric($id)) return FALSE;
        mysqli_query($_FG[$dbhandler], 'DELETE FROM `' . $table . '` WHERE `id`=' . $id . ' LIMIT 1' );
        if (mysqli_affected_rows($_FG[$dbhandler]) != 1) return FALSE;
        return TRUE;
    }


    // decode checkbox accumulated letters, using names from a table
    //////////////////////////////////////////////////////////////////////////
    function FG_decodecheckbox ($table, $string){
        $arrbuf = str_split ($string, 1);
        if ((!is_array($arrbuf))||(@count($arrbuf)<1)) return ' ';
        foreach($arrbuf as $letter) { 
            $ret = FG_dbgetbyfield ($table, 'id2', $letter);
            $output .= ' &nbsp; - ' . $ret['name'] . ' ';  
            }
        return $output;
        }



    //////////////////////////////////////////////////////////////////////////
    // LOGGING
    //////////////////////////////////////////////////////////////////////////
    /*
    Event codes:
    LOGINFAIL
    LOGINOK
    LOGOUTOK
    CHANGEDIP
    ORDINARYERROR
    FORMERROR
    ACLFAIL
    SENDMAIL
    HACKERATTACK
    */

    function FG_log ($event, $details) {
        global $_FG;

        if (!isset($_SESSION['user_id'])) $user_id = 0;
         else $user_id = $_SESSION['user_id'];
        $useragent = mysqli_real_escape_string($_FG['db0'], $_SERVER['HTTP_USER_AGENT']);
        $forwarded = mysqli_real_escape_string($_FG['db0'], $_SERVER['HTTP_X_FORWARDED_FOR']);
        $details = mysqli_real_escape_string($_FG['db0'], strip_tags($details));

        $result = mysqli_query($_FG['db0'], "INSERT INTO `log` (`datetime`, `ip`, `xforwardedf`, `useragent`, `userid`, `event`, `details`) VALUES (NOW(), '{$_SERVER['REMOTE_ADDR']}', '$forwarded', '$useragent', $user_id, '$event',  '$details')");
        // TODO: send mail to admin // if (mysqli_affected_rows($_FG['db0'])<1) {  }
    }



    //////////////////////////////////////////////////////////////////////////
    // FORM FUNCTIONS (other functions are loaded when first call to FGform_start)
    //////////////////////////////////////////////////////////////////////////
    function FG_form_start ($formname, $method = 'POST', $action = 'SELF') {
        global $_FG;
        include_once(CORE_PATH . '/forms.inc');
         
        $_FG['render']['extrahead'] .= '<script>$(document).ready( function() { $("#' . $formname . '").validationEngine(\'attach\'); });</script>';
        if ($action=='SELF') $action = '/' . $_FG['request'][0] . '/' . $_FG['request'][1] . '/';
        $_FG['trusted_channel'] = $method;
        $_FG['currentformname'] = $formname;
        if ($_FG['trusted_channel']=='POST')  $_FG['getpost'] = $_POST;  else  $_FG['getpost'] = $_GET;
        if (count($_FG['getpost'])>0)  $_FG['is_reception'] = TRUE;  

            // Determines if this form is for update (so retrieves DB data) or form is for new insert 
            // EDIT
            if ($_FG['request'][2]=='edit') {
            $id = FG_decode ($_FG['request'][3]);
            if (!is_numeric($id)) FG_error('Error en parámetro: dato malformado');
            echo $_FG['edittitle'];
            $_FG['buttontext'] = $_FG['editbutton'];
                if(!$_FG['is_reception']){
                $_FG['updateinfo'] = FG_dbget ($_FG['table'], $id);
                if ($_FG['updateinfo']===NULL) FG_error('Error en parámetro: registro inexistente');
                if (isset($_FG['datefields'])) FG_formatdb2date ($_FG['updateinfo'], $_FG['datefields']); // date format correction
                }
            $updatefield = '<input type="hidden" name="updatefield" value=' . FG_encode ($id) . '>';
            $_FG['is_update'] = TRUE;
            }
            // CLONATION
            else if ($_FG['request'][2]=='clone') {
            $id = FG_decode ($_FG['request'][3]);
            if (!is_numeric($id)) FG_error('Error en parámetro: dato malformado');
            echo $_FG['newregtitle'];
            $_FG['buttontext'] = $_FG['newregbutton'];
                if(!$_FG['is_reception']){
                $_FG['updateinfo'] = FG_dbget ($_FG['table'], $id);
                if ($_FG['updateinfo']===NULL) FG_error('Error en parámetro: registro inexistente');
                }
            }
            // NEW
            else {
            echo $_FG['newregtitle'];
            $_FG['buttontext'] = $_FG['newregbutton'];
            }
            // when coming by POST, without parameters in url but is set 'updatefield', this is also an update
            if($_FG['is_reception'])  if(isset($_FG['getpost']['updatefield'])) $_FG['is_update'] = TRUE;
            //////////////////////////

        if(!$_FG['is_reception']) 
        echo '<form action="' . $action . '" method="' . $method . '" id="' . $formname . '" enctype="multipart/form-data"><input type="hidden" name="MAX_FILE_SIZE" value="700000">' . $updatefield . ' 
        <center><table width=830 cellpadding=2 cellspacing=2 border=0><tr><td align="left" bgcolor="#cfcfff" colspan=2> &nbsp; &nbsp; <a href="javascript: history.go(-1)" title="volver a la pantalla anterior"><img src="/images/list/2/arrow-back-trans.png" border=0 width=16 height=16></a></td></tr>';

         else foreach($_FG['getpost'] as $key=>$data) {
            if (!is_array($data)) $_FG[$formname][$key]=mysqli_real_escape_string($_FG['db0'],$data); 
            else $_FG[$formname][$key]=$data;
            }
    }



    //////////////////////////////////////////////////////////////////////////
    // File details
    // $fieldslist is an array in the form:  array ('FieldName'=>'RowTitle', ... );
    //////////////////////////////////////////////////////////////////////////
    function FG_details ($sqltable, $fieldslist) {
        global $_FG;  
        if (!isset($_FG['request'][2])) FG_error('Error en parámetro: falta identificador de registro...');
        $id = FG_decode ($_FG['request'][2]);
            if (!is_numeric($id)) FG_error('Error en parámetro: dato malformado...');
        $file = FG_dbget($sqltable, $id);
            if($file===FALSE) FG_error('No existe el registro especificado...');
        echo '<center><table width=830 cellpadding=2 cellspacing=2 border=0><tr><td align="left" bgcolor="#cfcfff" colspan=2> &nbsp; &nbsp; <a href="javascript: history.go(-1)" title="volver a la pantalla anterior"><img src="/images/list/2/arrow-back-trans.png" border=0 width=16 height=16></a></td></tr>';

        if (isset($_FG['datefields'])) FG_formatdb2date ($file, $_FG['datefields']); // date format correction
        foreach ($file as $row=>$data) {
            if (array_key_exists($row, $fieldslist)){
            $FG_local_segment1 = $fieldslist[$row];
            if (isset($_FG['substitutions'][$row])) $FG_local_segment2 = FG_id2name ($_FG['substitutions'][$row], $data);
            else $FG_local_segment2 = $data;

            include (PUBLIC_PATH . '/template_sub_formrow.html');
            }
        }
        if (array_key_exists('FGphoto', $fieldslist)) {

        $photoscount =0;
        $photo = FG_mainphoto($row['id']);

/*
echo "<a href='/photos/{$photo}' class='highslide' onclick='return hs.expand(this)'><img src='/photos/t/{$photo}' align='left' width=320 class='imgarticle'></a>";
*/
        }

        echo '</table></center>';
    }




    //////////////////////////////////////////////////////////////////////////////////////
    function FG_mainphoto ($id){
        global $_FG;  
        global $photoscount;

//    $result = mysqli_query($_FG['db0'], "SELECT * FROM `photos` WHERE `article`=$id ORDER BY `id` ASC");
//    $photoscount = mysqli_num_rows($result);
//    if ($photoscount < 1) return FALSE;
//    $row = mysqli_fetch_assoc($result);
//    return $row['filename'];
    }





    /*

     Required fields:
      V  $params['searchtable']  string
      V  $params['labelslist']   array
      V  $params['fieldslist']   array
      V  $params['where_cond']  string
      V  $params['orderby'] 
      V  $params['order'] 
    */ 

    //////////////////////////////////////////////////////////////////////////
    function FG_wholelist ($params) {  
        global $_FG;
        include_once(CORE_PATH . '/lists.inc');

        $where_cond = ' ' . $params['where_cond'];
        $params['controls'] = array();  // no controls in list rows

        $stra = explode('_', $params['searchtable']);
        $_FG['baselink'] = $stra[1];

        // back to this page after deletion/modification
        $_SESSION['pageback'] = '/'.$_FG['request'][0].'/'.$_FG['request'][1].'/'.$_FG['request'][2].'/';

        // results table building
        $numfields = count ($params['labelslist']);
        if ($numfields<1) return;


        echo '<table width=830 cellpadding=2 cellspacing=2 border=0><tr><td align="right" bgcolor="#CFCFFF"><input id="printbutton" type="button" value="Imprimir listado" onClick="window.print()" /></form> &nbsp; &nbsp; </td></tr></table><table width=830 cellpadding=2 cellspacing=2 border=0 id="listtable"><thead><tr>';
        foreach ($params['labelslist'] as $label => $width){
            if ($width!=0) $txtwidth = ' width=' . $width; else $txtwidth = ''; 
            echo '<td height=30 align="center" bgcolor="#CFCFFF"' . $txtwidth . '><b>' . $label . '</b></td>'; 
            }
        echo '</tr></thead><tbody>';

 
        if (isset($params['orderby'])) {
            if (isset($params['order'])) $ascdesc = ' ' . $params['order'];  else $ascdesc = ' ASC';
            if(!is_array($params['orderby'])) $orderby = ' ORDER BY `' . $params['orderby'] . '`' . $ascdesc; 
            else { // process array
                 $orderby_temp = ' ORDER BY ';
                 foreach ($params['orderby'] as $orderx) { $orderby_temp .= '`' . $orderx . '`, '; }
                 $orderby = rtrim ($orderby_temp, ', ') . $ascdesc;
            }
        }  else  $orderby = '';

        $reqfields = FGlist_mkfieldslist ($params['fieldslist']);
        $result = mysqli_query($_FG['db0'], 'SELECT ' . $reqfields . ' FROM `' . $params['searchtable'] . '`' . $where_cond . $orderby   );

//echo 'SELECT ' . $reqfields . ' FROM `' . $params['searchtable'] . '`' . $where_cond . $orderby;
//return;

        if (mysqli_num_rows($result)<1) { echo '<tr><td><br>Sin resultados...</td></tr></tbody></table>'; return; } // no results to show

        while($fila = mysqli_fetch_assoc($result)) {
            FG_formatdb2date ($fila, $params['datefields']);
            FGlist_mkrow ($fila, $params['fieldslist'], $params['controls'], $params['substitutions']);
            }
        mysqli_free_result($result);

        echo <<<EOF
</tbody></table></center>
EOF;

    return $resulttotal;

    }


include_once(CORE_PATH . '/lists.inc');


    //////////////////////////////////////////////////////////////////////////
    // MAIL FUNCTION this function uses default values configured in 'free-gov-core/configuration.inc'
    //////////////////////////////////////////////////////////////////////////
    function FG_sendmail ($to, $subject, $message, $altmessage='', $fromname='' ) {
        global $_FG;
        include_once(CORE_PATH . '/lib/class.phpmailer.php');
         
        if(strlen($altmessage)<1) $altmessage = $message;
        if(strlen($fromname)<1) $fromname = MAILER_SMTP_FROMNAME;

        $mail = new PHPMailer();

        $mail->IsSMTP();
        $mail->Host = MAILER_SMTP_SERVER;
        $mail->SMTPAuth = true;     // turn on SMTP authentication
        $mail->Username = MAILER_SMTP_USER;  // SMTP username
        $mail->Password = MAILER_SMTP_PASS;  // SMTP password
        $mail->From = MAILER_SMTP_USER;
        $mail->FromName = $fromname;
        $mail->AddAddress($to);              // name is optional
        $mail->AddReplyTo(MAILER_SMTP_USER, MAILER_SMTP_FROMNAME);
        $mail->WordWrap = 50;                               // set word wrap to 50 characters
        //$mail->AddAttachment("/var/tmp/file.tar.gz");     // add attachments
        $mail->IsHTML(true);                                // set email format to HTML
        $mail->Subject = $subject;
        $mail->Body    = $message;
        $mail->AltBody = $altmessage;

        if(!$mail->Send())
          {
            FG_log ('SENDMAIL', $mail->ErrorInfo);
            return FALSE;
          }
        return TRUE;
    }



    // Encode-Decode simil-Base64 replacing "+/=" for "-_," for framework compatibility 
    // can pack arrays and complex variables
    /////////////////////////////////////////////////////////////////////
    function FG_encode ($input) {
        return strtr(base64_encode(serialize($input)), '+/=', '-_,');
    }


    function FG_decode ($input) {
        return unserialize(base64_decode(strtr($input, '-_,', '+/=')));
    }


