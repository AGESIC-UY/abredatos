<?php
    #
    #   ABREDATOS - Software de extracción, anonimización y publicación 
    #               de Datos Abiertos - SOFTWARE PUBLICO URUGUAYO
    # 
    #  Creado en el Municipio de Maldonado (http://www.municipiomaldonado.gub.uy)
    #  por Iris Montes de Oca (http://www.irismontesdeoca.com)
    #  en la plataforma de Gobierno Electrónico Free-gov (http://free-gov.org)
    #    
    #  Este Software de distribuye bajo los términos de la Licencia AGPL 3
    #  El texto de la licencia AGPL se encuentra an el archivo 'license.txt'
    #  (en idioma inglés), en el mismo paquete de distribución de este software.
    #
    #  El cumpliminto internacional de la Licencia AGPL requiere la inclusión
    #  del siguiente bloque de licenciamiento en idioma inglés, en cada archivo:
    #
    #
    #  This file is part of 'ABREDATOS' 
    #
    #  ABREDATOS - Open Data extraction and publishing toolkit.
    #  Copyright (C) 2013 Iris Montes de Oca <http://www.irismontesdeoca.com>
    #  working with Municipio de Maldonado <http://www.municipiomaldonado.gub.uy>
    #
    #  ABREDATOS is free software; you can redistribute it and/or modify
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
    #  Internet: http://www.municipiomaldonado.gub.uy/abredatos
    #
    #  This software is built on top of free-gov platform (http://free-gov.org)
    #
  
    header('Content-Type: text/plain');
    
    set_time_limit (0); // trata de aumentar al máximo el tiempo límite de ejecución de este script.
         
    $filesindataset = array();         
    //  Since this is an isolated script outside of the main free-gov framework, we must start importing some data and functions
    //  to deal with databases, URIs, etc. Following 3 lines are a subset of free-gov's FRONT_CONTROLLER
    define('PUBLIC_PATH', dirname(__FILE__));
    define('CORE_PATH', dirname(PUBLIC_PATH) . '/free-gov-core'); // Configuration & system files    
    include (CORE_PATH . '/core.inc');     // Include core functions, configuration file, db connection, etc.
              
    define('DATA_PATH', PUBLIC_PATH . '/opendata/');          
    if ($_GET['secret'] != ABREDATOS_SECRET)  {  // ABREDATOS_SECRET defined in "free-gov-core/.configuration" file
    //  We are dealing with a nasty visitor: let's redirect him far away... to INTERPOL website
    header('Location: http://www.interpol.int/es/Criminalidad/Delincuencia-inform%C3%A1tica/Ciberdelincuencia'); 
    //  Register the malformed intent, with details about hacking IP, proxy (if any), datetime, query and user agent
    FG_log ('PUBLIC_ATTACK', 'Query (FG_coded): ' . FG_encode($_SERVER['REQUEST_URI']) );
    }  
  
    $todo = array();
    $now  = time();
    
    $result = mysqli_query($_FG['db0'], 'SELECT * FROM `abredatos_datasets`');
    if(!$result) exit;
            while($fila = mysqli_fetch_assoc($result)) {
                    //if ($fila['lastrun']==0){
                  if (($fila['lastrun']+(3600*$fila['refreshtime'])) <= $now ) {
                      mysqli_query($_FG['db0'], "UPDATE `abredatos_datasets` SET `lastrun` = $now WHERE `id` = {$fila['id']}"); // done
                      $DBMS = FG_dbget('abredatos_DBMSs', $fila['DBMS']);
                      $driver = FG_dbget('abredatos_drivers', $DBMS['driver']);
                      $todo[] = array ($fila, $DBMS, $driver);
                      break;
                      }
                 } 

      include (CORE_PATH . '/lib/adodb5/adodb.inc.php');
      include (CORE_PATH . '/lib/pclzip.lib.php');
  
      foreach ($todo as $tododataset) {  // for each dataset to process
       // ADO connection for this dataset            
       $DB = NewADOConnection($tododataset[2]['module']);
       $DB->Connect($tododataset[1]['DBMS_server_URI'], $tododataset[1]['DBMS_username'], $tododataset[1]['DBMS_password'], $tododataset[1]['database_name']); 

      $result = mysqli_query($_FG['db0'], 'SELECT * FROM `abredatos_fields` WHERE `dataset` = ' . $tododataset[0]['id']);
      if(!$result) continue;
      while($fila = mysqli_fetch_assoc($result)) // $fields contains the tables/fields to retrieve from target database   
                   $fields[$fila['DBMS_table_name']][] = array('DBMS_field_name'=>$fila['DBMS_field_name'], 'name'=>$fila['name']);               
                   
       foreach ($fields as $tablename=>$field) {
           maketablefile ($tablename, $tododataset, $field);
           }
      mkmetadata($tododataset);
      mkzip ($tododataset);
      $DB->Close();
      exit(); // to save execution time, any other datasets will be processed on next script call made by CRON
      }
      
             
//////////////////////////////////////////////////////////////////////////////////////// 
////////////////////////////////////////////////////////////////////////////////////////     
     function mkzip($tododataset){
      
     global $filesindataset;       
     $cleanfilenamestr = cleanfilename($tododataset[0]['name'] . '-opendata.zip'); 
     echo $cleanfilenamestr . "\n";
     $filename = DATA_PATH . $cleanfilenamestr;     
     
     if (file_exists($filename)) unlink($filename);
     $zip = new PclZip($filename);
     
     foreach($filesindataset as $filename) 
       $zip->add (DATA_PATH . $filename, PCLZIP_OPT_REMOVE_ALL_PATH);     
     } 
  
      
//////////////////////////////////////////////////////////////////////////////////////// 
////////////////////////////////////////////////////////////////////////////////////////     
     function maketablefile($tablename, $tododataset, $field){
 
       global $DB, $filesindataset; 
       $cleanfilenamestr = cleanfilename($tododataset[0]['name'] . '-'  . $tablename . '.csv');
       $CSVfilename = DATA_PATH . $cleanfilenamestr;
       $filesindataset[] = $cleanfilenamestr;
      
      $DBMS_field_names = ' ';  // to compose fields to retrieve in SQL query
          foreach ($field as $fieldrow) {          
              if ($DBMS_field_names != ' ') $DBMS_field_names .= ','; 
              $DBMS_field_names .= ' ' . $fieldrow['DBMS_field_name'];
              $arrfieldnames[] = $fieldrow['DBMS_field_name'];
          }               
       $fp = fopen($CSVfilename,'w');        
       
       $numfields = count($arrfieldnames);
       $i=0;
       
       $rs = $DB->Execute('select ' . $DBMS_field_names . ' from ' . $tablename);
            while ($array = $rs->FetchRow()) {
            $content = '';
               foreach ($arrfieldnames as $field){
               $array[$field] = str_replace(array("\r\n","\r","\n"),'', strip_tags($array[$field])); 
               $content .=  '"' . addcslashes($array[$field], '"'); // escape only double quotes 
               if(++$i<$numfields) $content .= '", '; else { $content .= "\"\n"; $i=0; } 
               }
            $content = mb_convert_encoding($content, 'ISO-8859-1');   
            fwrite($fp, $content);                         
            }                  
       $rs->Close();
       fclose($fp);    
      }
 
 
//////////////////////////////////////////////////////////////////////////////////////// 
////////////////////////////////////////////////////////////////////////////////////////     
     function mkmetadata($data){

     global $_FG, $filesindataset;     
     $cleanfilenamestr = cleanfilename($data[0]['name'] . '-metadata.txt');
     $filesindataset[] = $cleanfilenamestr;
     $licencia = FG_dbget('abredatos_licenses', $data[0]['license']);
     $datetime = date('d-m-Y / H:i:s');  
     
     $showfilesindataset = '';
     foreach($filesindataset as $filename) $showfilesindataset .= "\t" . $filename . "\n";

$metadata = <<<EOF
*
*  METADATOS DEL DATASET "{$data[0]['name']}"
*
*     GENERADO CON EL SOFTWARE PUBLICO ABREDATOS 
*     http://municipiomaldonado.gub.uy/abredatos
*
*

- NOMBRE DEL DATASET: {$data[0]['name']}
- CHARSET: ISO8859-1
- INSTITUCION QUE LIBERA LOS DATOS: {$data[0]['institution']}
- GENERADO EN FECHA/HORA: $datetime
- INTERVALO DE REGENERACION (HORAS): {$data[0]['refreshtime']}
- LICENCIA DE LOS DATOS: {$licencia['name']}
- CATEGORIA DE DATOS: {$data[0]['category']}
- DESCRIPCION DEL DATASET: {$data[0]['description']}


- FICHEROS CONTENIDOS EN EL DATASET:

  $showfilesindataset
EOF;

      file_put_contents(DATA_PATH . $cleanfilenamestr, $metadata);                 
      }
      
           
//////////////////////////////////////////////////////////////////////////////////////// 
////////////////////////////////////////////////////////////////////////////////////////   
     function cleanfilename($string) {
	$string = trim($string);
	$string = strtr($string,"ÀÁÂÃÄÅàáâãäåÒÓÔÕÖØòóôõöøÈÉÊËèéêëÇçÌÍÎÏìíîïÙÚÛÜùúûüÿÑñ",
                                "aaaaaaaaaaaaooooooooooooeeeeeeeecciiiiiiiiuuuuuuuuynn");
	$string = strtolower($string);
	$string = preg_replace('#([^.a-z0-9]+)#i', '-', $string);
        $string = preg_replace('#-{2,}#','-',$string);
        $string = preg_replace('#-$#','',$string);
        $string = preg_replace('#^-#','',$string);
	return $string;
}



