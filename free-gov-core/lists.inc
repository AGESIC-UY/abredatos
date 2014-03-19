<?php
    #         ____
    #        / __/________  ___        ____ _____ _   __
    #       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
    #      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ /
    #     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
    #                               /____/
    #
    #  This file is part of 'Free-gov' - free-gov-core/lists.inc
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
    function FG_buildsearch2(&$params, &$where_cond){
      global $_FG;

        $FG_searchcond = array ('CONTENGA', '=', '>', '<', '>=', '<='); // Search operations array

        // FILTER REMOVAL
        if ($_FG['request'][2]==$params['searchtable'].'_removefilter') { unset ($_GET[$params['searchtable'].'_fl']); unset ($_GET[$params['searchtable'].'_va']); unset ($_GET[$params['searchtable'].'_op']); unset ($_SESSION[$params['searchtable'].'search']); }  // process search filter removal


        foreach ($params['fieldsearch'] as $field=>$label)  $params['select'] .= '<option value=' . $field . '>' . $label  . '</option>';

        foreach ($FG_searchcond as $i=>$field)  $params['select2'] .= '<option value=' . $i . '>' . $field  . '</option>';

        if (isset($_GET[$params['searchtable'].'_fl'])) { $_SESSION[$params['searchtable'].'search']['fl'] = $_GET[$params['searchtable'].'_fl']; 
            $_SESSION[$params['searchtable'].'search']['op'] = $_GET[$params['searchtable'].'_op']; $_SESSION[$params['searchtable'].'search']['va'] = $_GET[$params['searchtable'].'_va'];  }
       

 
        $where_cond = '';
        if (isset($_SESSION[$params['searchtable'].'search']['fl'])){
            if ($_SESSION[$params['searchtable'].'search']['op'] == '0') { // search tipe is "CONTAINS"
                $where_cond = ' WHERE `' . $_SESSION[$params['searchtable'].'search']['fl'] . "` LIKE '%" . $_SESSION[$params['searchtable'].'search']['va'] . "%'";
            }
            else {
                $where_cond = ' WHERE `' . $_SESSION[$params['searchtable'].'search']['fl'] . '` ' . $FG_searchcond[$_SESSION[$params['searchtable'].'search']['op']] . " '" . $_SESSION[$params['searchtable'].'search']['va'] . "' ";
            }
          $params['filterbar'] = '<tr><td align="center" bgcolor="#CFCFFF"><a href="' . '/'.$_FG['request'][0].'/'. $_FG['request'][1] . '/'.$params['searchtable'] .'_removefilter' . '" title="remover filtro"><img src="/images/list/1/delete_16-trans.png" width=16 height=16 border=0></a> FILTRADO ACTIVO: <b>' . $params['fieldsearch'][$_SESSION[$params['searchtable'].'search']['fl']]  . '</b> ' .  $FG_searchcond[$_SESSION[$params['searchtable'].'search']['op']] . ' <b>' . $_SESSION[$params['searchtable'].'search']['va'] . '</b></td></tr>';

        }


$params['searchbar'] = <<<EOF

        <table width=830 cellpadding=2 cellspacing=2 border=0><tr><td>
        <div>
        <fieldset id="search">
        <div class="collapse" ></div>
        <div class="expand" ></div>
        <div id="search1">
        <center><form id="form1" action="/{$_FG['request'][0]}/{$_FG['request'][1]}/" method="GET" enctype="multipart/form-data"><table width=830 cellpadding=2 cellspacing=2 border=0><tr><td align="center" bgcolor="#cfcfff"><select name="{$params['searchtable']}_fl" id="{$params['searchtable']}_fl">{$params['select']}</select> &nbsp; &nbsp; <select name="{$params['searchtable']}_op" id="{$params['searchtable']}_op">{$params['select2']}</select>  &nbsp; &nbsp; <input type="text" name="{$params['searchtable']}_va"  id="{$params['searchtable']}_va" value="" class="validate[required,minSize[1]] formfield_short"> &nbsp; &nbsp; <input type="submit" name="btn"     value="buscar"></td></tr></table></form>
        </div>
        </fieldset> 
        </div></td></tr></table>
EOF;


}




   //////////////////////////////////////////////////////////////////////////
    // LIST FUNCTIONS (other functions are loaded when first call to FG_list)
    /*

     Required fields:
      V  $params['searchtable']  string
      V  $params['labelslist']   array
      V  $params['fieldslist']   array
      V  $params['controls']     array
      V  $params['fieldsearch']  array
        
      V  $params['where_cond']  string
      V  $params['value']    // ignored for this control
      V  $params['crud_no_add'] 
      V  $params['crud_no_search'] 

      V  $params['orderby'] 
      V  $params['order'] 
    */ 
    //////////////////////////////////////////////////////////////////////////
    function FG_list2 ($params) {
        global $_FG;
        include_once(CORE_PATH . '/lists-aux.inc');
   
        $where_cond = ' ' . $params['where_cond'];
        if (!isset($params['controls']))  $params['controls'] = array();

        $stra = explode('_', $params['searchtable']);
        $_FG['baselink'] = $stra[1];


if($params['crud_no_search']!==TRUE){
        $_FG['render']['extrahead'] .= <<<EOF
<script type="text/javascript" src="/js/jquery.jcollapser-1.2.2.js"></script>
<script type="text/javascript" src="/js/jquery.cookie.js?format=txt"></script>
<script type="text/javascript">
    $(function() {
        $("#search").jcollapser({target:'#search1', state:'collapsed'});
    });
</script>
<style type="text/css">
.collapse {
    background: transparent url('/images/list/1/hide-trans.png') no-repeat scroll 0% 0%;
    height: 16px;
    position: relative;
    width: 16px;
}
.expand {
    background:transparent url('/images/list/1/search.png') no-repeat scroll 0% 0%;
    display:none;
    height:16px;
    position:relative;
    width:63px;
}
</style>
<script>$(document).ready( function() { $("#form1").validationEngine('attach'); });</script>
<script>$(document).ready(function(){
		$('.shl').hover(function(){
			$(this).children().addClass('datahighlight');
		},function(){
			$(this).children().removeClass('datahighlight');
		});
});</script>
EOF;
}


        echo <<<EOF
<div id="confirmDelete" title="Confirmación de borrado">
<p><span class="ui-icon ui-icon-circle-close" style="float:left; margin:0 7px 20px 0;"></span> 
 ¿confirma que desea borrar este registro?</p></div>
<script type="text/javascript">
$("#confirmDelete").dialog({ modal: true, bgiframe: true, width: 400, height: 200, autoOpen: false, draggable: false, resizable: false }); 
function confirmDelete(delUrl) { $('#confirmDelete').dialog('option', 'buttons', { "No borrarlo, me arrepentí...": function() { $(this).dialog("close"); },
"Borrar": function() { window.location.href = delUrl; }  }); $('#confirmDelete').dialog('open'); }
</script>
EOF;

        // search environment
        if($params['crud_no_search']!==TRUE){
            FG_buildsearch2($params, $where_cond);
        }


        // pagination environment
        $resultsperpage = 10;
        if (isset($_FG['request'][2])) { if (!is_numeric($_FG['request'][2])) $reqpage=1; else $reqpage=$_FG['request'][2]; }
        else $reqpage=1;
        $jump =  ($reqpage-1) * $resultsperpage; // how many results to jump over?          
        $countresult = mysqli_query($_FG['db0'], 'SELECT COUNT(*) FROM `' . $params['searchtable'] . '`' . $where_cond);
        $buffertotal = mysqli_fetch_assoc($countresult);  mysqli_free_result($countresult);
        $resulttotal = $buffertotal['COUNT(*)'];
        $from = $jump + 1;
        $to  = $from + ($resultsperpage -1);   
        if ($to > $resulttotal) $to = $resulttotal; 

        if ($resulttotal > 0)
        $pagination = '<center> RESULTADOS: '.$resulttotal.' &nbsp; | &nbsp; Mostrando del '.$from.' al '.$to . ' &nbsp; | &nbsp; &nbsp; &nbsp;' . FGpaginate($reqpage, 
                $resulttotal, $resultsperpage, '/'.$_FG['request'][0].'/'.$_FG['request'][1].'/', 20) . '</center>';
        else $pagination = '<center> RESULTADOS: '.$resulttotal. ' (no hay registros disponibles)';


        // "order by" environment
        // TODO

        // back to this page after deletion/modification
        $_SESSION['pageback'] = '/'.$_FG['request'][0].'/'.$_FG['request'][1].'/'.$_FG['request'][2].'/';

        // results table building
        $numfields = count ($params['labelslist']);
        if ($numfields<1) return;

        $numcontrols = count($params['controls']);
        if ($numcontrols>0) {
            $controlswidth = $numcontrols * 24;
            $controlshead = '<td colspan="'.$numcontrols.'" width='.$controlswidth.'>';
        }
        else $controlshead ='';


        echo '<center>' . $params['searchbar']; // show collapsable search tool



if ($params['crud_no_add']===true) $addregister = '&nbsp;'; else $addregister = '<a href="/'. $_FG['request'][0] .'/' . $_FG['baselink'] . '_c" title="agregar nuevo registro"><img src="/images/list/2/add-trans.png" width=16 height=16 border=0></a>';

//unset ($_SESSION['menu']);
//var_dump($_SESSION); 
//var_dump($_GET);

        echo '<table width=830 cellpadding=2 cellspacing=2 border=0><tr><td align="center" bgcolor="#CFCFFF"><table width="100%" cellpadding=0 cellspacing=0 border=0><tr><td width=20>' . $addregister . '</td><td>'.$pagination . '</td></tr></table></td></tr>' . $params['filterbar'] . '</table><table width=830 cellpadding=2 cellspacing=2 border=0 id="listtable"><thead><tr>';
        foreach ($params['labelslist'] as $label => $width){
            if ($width!=0) $txtwidth = ' width=' . $width; else $txtwidth = ''; 
            echo '<td height=30 align="center" bgcolor="#CFCFFF"' . $txtwidth . '><b>' . $label . '</b></td>'; 
            }
        echo $controlshead . '</tr></thead><tbody>';


        if (isset($params['order'])) $ascdesc = ' ' . $params['order']; else $ascdesc = ' ASC';
        $orderby = ''; if (isset($params['orderby']))  $orderby = ' ORDER BY `' . $params['orderby'] . '`' . $ascdesc; 

        $reqfields = FGlist_mkfieldslist ($params['fieldslist']);
        $result = mysqli_query($_FG['db0'], 'SELECT ' . $reqfields . ' FROM `' . $params['searchtable'] . '`' . $where_cond . $orderby . ' LIMIT ' . $jump . ', ' . $resultsperpage  );

//echo 'SELECT ' . $reqfields . ' FROM `' . $params['searchtable'] . '`' . $where_cond . $orderby . ' LIMIT ' . $jump . ', ' . $resultsperpage;

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





   //////////////////////////////////////////////////////////////////////////
    function FG_buildsearch(&$params, &$where_cond){
      global $_FG;

        $FG_searchcond = array ('CONTENGA', '=', '>', '<', '>=', '<='); // Search operations array

        // FILTER REMOVAL
        if ($_FG['request'][2]==$params['searchtable'].'_removefilter') { unset ($_GET[$params['searchtable'].'_fl']); unset ($_GET[$params['searchtable'].'_va']); unset ($_GET[$params['searchtable'].'_op']); unset ($_SESSION[$params['searchtable'].'search']); }  // process search filter removal


        foreach ($params['fieldsearch'] as $field=>$label)  $params['select'] .= '<option value=' . $field . '>' . $label  . '</option>';

        foreach ($FG_searchcond as $i=>$field)  $params['select2'] .= '<option value=' . $i . '>' . $field  . '</option>';

        if (isset($_GET[$params['searchtable'].'_fl'])) { $_SESSION[$params['searchtable'].'search']['fl'] = $_GET[$params['searchtable'].'_fl']; 
            $_SESSION[$params['searchtable'].'search']['op'] = $_GET[$params['searchtable'].'_op']; $_SESSION[$params['searchtable'].'search']['va'] = $_GET[$params['searchtable'].'_va'];  }
       
        if (strlen($where_cond)>0){ // there is a legacy WHERE COND, passed when building list. We must append this value
            $where_cond_orig = $where_cond;
            $where_cond_append = str_replace ( 'WHERE', 'AND',  $where_cond);
        }

 
        $where_cond = '';
        if (isset($_SESSION[$params['searchtable'].'search']['fl'])){
            if ($_SESSION[$params['searchtable'].'search']['op'] == '0') { // search tipe is "CONTAINS"
                $where_cond = ' WHERE `' . $_SESSION[$params['searchtable'].'search']['fl'] . "` LIKE '%" . $_SESSION[$params['searchtable'].'search']['va'] . "%'" . $where_cond_append;
            }
            else {
                $where_cond = ' WHERE `' . $_SESSION[$params['searchtable'].'search']['fl'] . '` ' . $FG_searchcond[$_SESSION[$params['searchtable'].'search']['op']] . " '" . $_SESSION[$params['searchtable'].'search']['va'] . "' "  . $where_cond_append;
            }
          $params['filterbar'] = '<tr><td align="center" bgcolor="#CFCFFF"><a href="' . '/'.$_FG['request'][0].'/'. $_FG['request'][1] . '/'.$params['searchtable'] .'_removefilter' . '" title="remover filtro"><img src="/images/list/1/delete_16-trans.png" width=16 height=16 border=0></a> FILTRADO ACTIVO: <b>' . $params['fieldsearch'][$_SESSION[$params['searchtable'].'search']['fl']]  . '</b> ' .  $FG_searchcond[$_SESSION[$params['searchtable'].'search']['op']] . ' <b>' . $_SESSION[$params['searchtable'].'search']['va'] . '</b></td></tr>';
        }
          else  $where_cond = $where_cond_orig;


$params['searchbar'] = <<<EOF

        <table width=830 cellpadding=2 cellspacing=2 border=0><tr><td>
        <div>
        <fieldset id="search">
        <div class="collapse" ></div>
        <div class="expand" ></div>
        <div id="search1">
        <center><form id="form1" action="/{$_FG['request'][0]}/{$_FG['request'][1]}/" method="GET" enctype="multipart/form-data"><table width=830 cellpadding=2 cellspacing=2 border=0><tr><td align="center" bgcolor="#cfcfff"><select name="{$params['searchtable']}_fl" id="{$params['searchtable']}_fl">{$params['select']}</select> &nbsp; &nbsp; <select name="{$params['searchtable']}_op" id="{$params['searchtable']}_op">{$params['select2']}</select>  &nbsp; &nbsp; <input type="text" name="{$params['searchtable']}_va"  id="{$params['searchtable']}_va" value="" class="validate[required,minSize[1]] formfield_short"> &nbsp; &nbsp; <input type="submit" name="btn"     value="buscar"></td></tr></table></form>
        </div>
        </fieldset> 
        </div></td></tr></table>
EOF;
}


   //////////////////////////////////////////////////////////////////////////
    // LIST FUNCTIONS (other functions are loaded when first call to FG_list)
    /*

     Required fields:
      V  $params['searchtable']  string
      V  $params['labelslist']   array
      V  $params['fieldslist']   array
      V  $params['controls']     array
         $params['controls_baseurl'] string (optional)  

      V  $params['fieldsearch']  array
        
      V  $params['where_cond']  string
      V  $params['value']    // ignored for this control
      V  $params['crud_no_add'] 
      V  $params['crud_no_search'] 

      V  $params['orderby'] 
      V  $params['order'] 
    */ 
    //////////////////////////////////////////////////////////////////////////
    function FG_list ($params) {
        global $_FG;
        include_once(CORE_PATH . '/lists-aux.inc');
   
        $where_cond = ' ' . $params['where_cond'];
        if (!isset($params['controls']))  $params['controls'] = array();

        $stra = explode('_', $params['searchtable']);
        $_FG['baselink'] = $stra[1];
        if (strlen($params['controls_baseurl'])>0) $_FG['baselink'] =  $params['controls_baseurl'];


if($params['crud_no_search']!==TRUE){
        $_FG['render']['extrahead'] .= <<<EOF
<script type="text/javascript" src="/js/jquery.jcollapser-1.2.2.js"></script>
<script type="text/javascript" src="/js/jquery.cookie.js?format=txt"></script>
<script type="text/javascript">
    $(function() {
        $("#search").jcollapser({target:'#search1', state:'collapsed'});
    });
</script>
<style type="text/css">
.collapse {
    background: transparent url('/images/list/1/hide-trans.png') no-repeat scroll 0% 0%;
    height: 16px;
    position: relative;
    width: 16px;
}
.expand {
    background:transparent url('/images/list/1/search.png') no-repeat scroll 0% 0%;
    display:none;
    height:16px;
    position:relative;
    width:63px;
}
</style>
EOF;
}


        $_FG['render']['extrahead'] .= <<<EOF
<script>$(document).ready( function() { $("#form1").validationEngine('attach'); });</script>
<script>$(document).ready(function(){
		$('.shl').hover(function(){
			$(this).children().addClass('datahighlight');
		},function(){
			$(this).children().removeClass('datahighlight');
		});
});</script>
EOF;

        echo <<<EOF
<div id="confirmDelete" title="Confirmación de borrado">
<p><span class="ui-icon ui-icon-circle-close" style="float:left; margin:0 7px 20px 0;"></span> 
 ¿confirma que desea borrar este registro?</p></div>
<script type="text/javascript">
$("#confirmDelete").dialog({ modal: true, bgiframe: true, width: 400, height: 200, autoOpen: false, draggable: false, resizable: false }); 
function confirmDelete(delUrl) { $('#confirmDelete').dialog('option', 'buttons', { "No borrarlo, me arrepentí...": function() { $(this).dialog("close"); },
"Borrar": function() { window.location.href = delUrl; }  }); $('#confirmDelete').dialog('open'); }
</script>
EOF;
        // search environment
        if($params['crud_no_search']!==TRUE){
            FG_buildsearch($params, $where_cond);
        }


        // pagination environment
        $resultsperpage = 10;
        if (isset($_FG['request'][2])) { if (!is_numeric($_FG['request'][2])) $reqpage=1; else $reqpage=$_FG['request'][2]; }
        else $reqpage=1;
        $jump =  ($reqpage-1) * $resultsperpage; // how many results to jump over?          
        $countresult = mysqli_query($_FG['db0'], 'SELECT COUNT(*) FROM `' . $params['searchtable'] . '`' . $where_cond);
        $buffertotal = mysqli_fetch_assoc($countresult);  mysqli_free_result($countresult);
        $resulttotal = $buffertotal['COUNT(*)'];
        $from = $jump + 1;
        $to  = $from + ($resultsperpage -1);   
        if ($to > $resulttotal) $to = $resulttotal; 

        if ($resulttotal > 0)
        $pagination = '<center> RESULTADOS: '.$resulttotal.' &nbsp; | &nbsp; Mostrando del '.$from.' al '.$to . ' &nbsp; | &nbsp; &nbsp; &nbsp;' . FGpaginate($reqpage, 
                $resulttotal, $resultsperpage, '/'.$_FG['request'][0].'/'.$_FG['request'][1].'/', 20) . '</center>';
        else $pagination = '<center> RESULTADOS: '.$resulttotal. ' (no hay registros disponibles)';


        // "order by" environment
        // TODO

        // back to this page after deletion/modification
        $_SESSION['pageback'] = '/'.$_FG['request'][0].'/'.$_FG['request'][1].'/'.$_FG['request'][2].'/';

        // results table building
        $numfields = count ($params['labelslist']);
        if ($numfields<1) return;

        $numcontrols = count($params['controls']);
        if ($numcontrols>0) {
            $controlswidth = $numcontrols * 24;
            $controlshead = '<td colspan="'.$numcontrols.'" width='.$controlswidth.'>&nbsp;</td>';
        }
        else $controlshead ='';

        echo '<center>' . $params['searchbar']; // show collapsable search tool



if ($params['crud_no_add']===true) $addregister = '&nbsp;'; 
else { 
      if (isset($params['crud_add'])) $addpage = $params['crud_add'];
      else $addpage = '/' . $_FG['request'][0] .'/' . $_FG['baselink'] . '_c';
     $addregister = '<a href="' . $addpage . '" title="agregar nuevo registro"><img src="/images/list/2/add-trans.png" width=16 height=16 border=0></a>';
     }

//unset ($_SESSION['menu']);
//var_dump($_SESSION); 
//var_dump($_GET);

        echo '<table width=830 cellpadding=2 cellspacing=2 border=0><tr><td align="center" bgcolor="#CFCFFF"><table width="100%" cellpadding=0 cellspacing=0 border=0><tr><td width=20>' . $addregister . '</td><td>'.$pagination . '</td></tr></table></td></tr>' . $params['filterbar'] . '</table><table width=830 cellpadding=2 cellspacing=2 border=0 id="listtable"><thead><tr>';
        foreach ($params['labelslist'] as $label => $width){
            if ($width!=0) $txtwidth = ' width=' . $width; else $txtwidth = ''; 
            echo '<td height=30 align="center" bgcolor="#CFCFFF"' . $txtwidth . '><b>' . $label . '</b></td>'; 
            }
        echo $controlshead . '</tr></thead><tbody>';

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
        $result = mysqli_query($_FG['db0'], 'SELECT ' . $reqfields . ' FROM `' . $params['searchtable'] . '`' . $where_cond . $orderby . ' LIMIT ' . $jump . ', ' . $resultsperpage  );

//echo 'SELECT ' . $reqfields . ' FROM `' . $params['searchtable'] . '`' . $where_cond . $orderby . ' LIMIT ' . $jump . ', ' . $resultsperpage;

        if (mysqli_num_rows($result)<1) { echo '<tr><td><br>Sin resultados...</td></tr></tbody></table>'; return; } // no results to show

        while($fila = mysqli_fetch_assoc($result)){
            FG_formatdb2date ($fila, $params['datefields']);
                if (isset($params['callbacks'])) { foreach ($params['callbacks'] as $data=>$func)  $fila[$data]= $func($fila[$data]); }
            FGlist_mkrow ($fila, $params['fieldslist'], $params['controls'], $params['substitutions']);
            }

        mysqli_free_result($result);

        echo <<<EOF
</tbody></table></center>
EOF;

    return $resulttotal;
    }



