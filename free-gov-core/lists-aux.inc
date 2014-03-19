<?php
    #         ____
    #        / __/________  ___        ____ _____ _   __
    #       / /_ / ___/ _ \/ _ \______/ __ `/ __ \ | / /
    #      / __// /  /  __/  __/_____/ /_/ / /_/ / |/ /
    #     /_/  /_/   \___/\___/      \__, /\____/|___/   > http://free-gov.org
    #                               /____/
    #
    #  This file is part of 'Free-gov' - free-gov-core/lists-aux.inc
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


global $_FG;

$_FG['list_ctrl']['edit'] = <<<EOF
<a href="###_c/edit/***" title="Editar este registro"><img src="/images/list/1/doc-edit-trans.png" width=16 height=16 border=0></a>
EOF;

/*
if (isset($_FG['customcontrol']['url'])){
$_FG['list_ctrl']['edit'] = <<<EOF
<a href="/{$_FG['request'][0]}/{$_FG['customcontrol']['url']}/edit/***" title="Editar este registro"><img src="/images/list/1/doc-edit-trans.png" width=16 height=16 border=0></a>
EOF;
}
*/

$_FG['list_ctrl']['delete'] = <<<EOF
<a href="javascript:void(0)" onclick="confirmDelete('###_d/***');"  title="Borrar este registro"><img src="/images/list/1/delete-trans.png" width=16 height=16 border=0></a>
EOF;

$_FG['list_ctrl']['chart'] = <<<EOF
<a href="###_ch/***" title="Ver gráficos"><img src="/images/list/2/chart-trans.png" width=16 height=16 border=0></a>
EOF;

$_FG['list_ctrl']['details'] = <<<EOF
<a href="###_f/***" title="Ver ficha completa"><img src="/images/list/2/magnifier-trans.png" width=16 height=16 border=0></a>
EOF;

$_FG['list_ctrl']['modal'] = <<<EOF
<a onclick="closemymodal('###', '***');" href="#" title="Seleccionar"><img src="/images/list/2/arrow-curve-trans.png" width=16 height=16 border=0></a>
EOF;

$_FG['list_ctrl']['print'] = <<<EOF
<a href="###_p/***" title="Imprimir" class="modalprint"><img src="/images/list/1/print-trans.png" width=16 height=16 border=0></a>
EOF;


$_FG['list_ctrl']['flag_0'] = <<<EOF
<a href="javascript:void(0)" onclick="confirmFlag('###_flag/***');" title="Marcar"><img src="/images/list/1/ball_grey_16-trans.png" width=16 height=16 border=0></a>
EOF;

$_FG['list_ctrl']['flag_1'] = <<<EOF
<a href="#" title="Marcado en fecha: ###"><img src="/images/list/2/flag-trans.png" width=16 height=16 border=0></a>
EOF;

//$_FG['list_ctrl']['clone'] = <<<EOF
//<a href="###_clone/***" title="Clonar y editar"><img src="/images/list/1/clone-trans.png" width=16 height=16 border=0></a>
//EOF;
$_FG['list_ctrl']['clone'] = <<<EOF
<a href="###_c/clone/***" title="Nuevo registro colnando estos datos"><img src="/images/list/1/clone-trans.png" width=16 height=16 border=0></a>
EOF;


$_FG['list_ctrl']['spreadsheet'] = <<<EOF
<a href="###_x/***" title="Descargar planilla electrónica"><img src="/images/list/2/app-table-trans.png" width=16 height=16 border=0></a>
EOF;


    //////////////////////////////////////////////////////////////////////////
    // Function FGpaginate
    // current:   current page
    // total:     total registers in table
    // per_page:  registers per page
    // link:      link text
    // maxpags:   optional max number of page links to be presented
    // RET:       returns a string of pagination links
    function FGpaginate($current, $total, $per_page, $link, $maxpags=0) {
      $total_pages = ceil($total/$per_page);
      $previous = $current - 1;
      $next = $current + 1;
      $minimum = $maxpags ? max(1, $current-ceil($maxpags/2)): 1;
      $maximum = $maxpags ? min($total_pages, $current+floor($maxpags/2)): $total_pages;
      if ($current>1)
        $text = '<a href="'.$link.$previous.'">&laquo;</a> ';
      else
        $text = '<b>&laquo;</b> ';
      if ($minimum!=1) $text.= '... ';
      for ($i=$minimum; $i<$current; $i++)
        $text .= '<a href="'.$link.$i.'">'.$i.'</a> ';
      $text .= '<b>'.$current.'</b> ';
      for ($i=$current+1; $i<=$maximum; $i++)
        $text .= '<a href="'.$link.$i.'">'.$i.'</a> ';
      if ($maximum!=$total_pages) $text.= "... ";
      if ($current<$total_pages)
        $text .= '<a href="'.$link.$next.'">&raquo;</a>';
      else
        $text .= '<b>&raquo;</b>';
      return $text;
    }



    // Fields list to be used for fields retieving in SQL SELECT statments
    //////////////////////////////////////////////////////////////////////////
    function FGlist_mkfieldslist ($fieldslist) {

        if(!in_array('id', $fieldslist)) $fieldslist[] = 'id';
        $ret = '';
        $flag = 0;
        foreach ($fieldslist as $field) {
            if ($flag!=0) $ret .= ', ';
            $ret .= '`' . $field . '`';
            $flag = 1;
            }
        return $ret;
    }


// $_FG['list_no_encode']
    //////////////////////////////////////////////////////////////////////////
    function FGlist_mkrow ($rowdata, $reqfields, $controls, $substitutions) {
        global $_FG;

        $toSave = array();

        echo '<tr class="shl">';
        foreach ($rowdata as $fieldname => $field) {
            $toSave[$fieldname] = $field; 
            if ($fieldname=='id') { $hashid = FG_encode($field);  if(!in_array('id', $reqfields)) { continue; } }
            if ($fieldname=='flag') { $flag= $field; continue; }
                if (isset($substitutions[$fieldname])) { echo '<td bgcolor="#eeeeee">' . FG_id2name ($substitutions[$fieldname], $field) .'</td>';  }
                else { echo '<td bgcolor="#eeeeee">' . $field .'</td>'; }
            }

        if (is_array($controls))
        { 
        foreach ($controls as $control) {

            if(is_array($control)) {

                $_FG['list_ctrl']['custom'] = "<a href=\"{$control['url']}\" title=\"{$control['title']}\" {$control['a_extras']}><img src=\"{$control['icon']}\" width=16 height=16 border=0></a>";
                $controlstring = str_replace('***', $hashid, $_FG['list_ctrl']['custom']);

            }
            else {
              if($control=='modal') { // modal control
                $controlstring = str_replace('###',  $toSave['name'], str_replace('***', $toSave['id'], $_FG['list_ctrl'][$control]));
                }
              else if ($control=='flag') { // flag control
                if ($flag==0) { $controlstring = str_replace('###', '/'.$_FG['request'][0] . '/' . $_FG['baselink'] , str_replace('***', $hashid, $_FG['list_ctrl']['flag_0'])); }
                else { $controlstring = str_replace('###', $flag, $_FG['list_ctrl']['flag_1']); }
                }
              else { // normal control
                $controlstring = str_replace('###', '/'.$_FG['request'][0] . '/' . $_FG['baselink'] , str_replace('***', $hashid, $_FG['list_ctrl'][$control]));
                }
            }   
            echo '<td bgcolor="#eeeeee" align="center" width=24>' . $controlstring .'</td>';
            }  //foreach
        }
        echo '</tr>';
    }



/*

<table width=830 cellpadding=2 cellspacing=2 border=0 id="listtable">
<thead>
<tr>
<td height=30 align="center" bgcolor="#CFCFFF" width=350><b>Nombre</b></td><td height=30 align="center" bgcolor="#CFCFFF" width=100><b>Cédula</b></td><td height=30 align="center" bgcolor="#CFCFFF" width=200><b>Informante</b></td><td height=30 align="center" bgcolor="#CFCFFF"><b>Fallo</b></td><td colspan="2" width=48>&nbsp;</td>

</tr></thead>





<tbody>
<tr class="shl">
<td bgcolor="#eeeeee">Correa González, Pablo David</td>
<td bgcolor="#eeeeee">3.476.909-0</td>
<td bgcolor="#eeeeee">Pepe Potamo</td>
<td bgcolor="#eeeeee">aprobado</td>
<td bgcolor="#eeeeee"></td>
<td bgcolor="#eeeeee" align="center" width=24><a href="/geps/jornales2012_f/czoyOiIyNCI7" title="Ver ficha completa"><img src="/images/list/2/magnifier-trans.png" width=16 height=16 border=0></a></td>
<td bgcolor="#eeeeee" align="center" width=24><a href="/geps/jornales2012_c/edit/czoyOiIyNCI7" title="Editar este registro"><img src="/images/list/1/doc-edit-trans.png" width=16 height=16 border=0></a></td>

</tr>
</tbody></table>



*/













