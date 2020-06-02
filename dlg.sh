#!/bin/bash

BdD=(\
  'compile:Compiler'
  'run C:Exécuter anglais'
  'run fr_FR.UTF-8:Exécuter Français'
  'save_src:Sauvegarder sources'
  ) # Fin BdD

##############################

function compile()
{
  make
}

##############################

function run()
{
  echo "Rien à tester" ; read rep ; return
  LANG=$2 ./dialog --caption "Pour test" --yesno "Sauvegarder\n$(for f in ${fichiers[@]} ; do echo "- $f"; done)\nDans ${svgFile} ?"
}

##############################

function save_src()
{
  svgFile="/home/jpv/sauvegarde-dialog-$(date +%Y%m%d-%H%M%S).tar.gz"
  fichiers=(\
    dlg.css
    dlg.h
    dlg-common.c
    dlg-main.c
    dlg-menu.c
    dlg-yesno.c
    dlg.sh
    Makefile
    )
msg="Sauvegarder\n\n$(for f in ${fichiers[@]} ; do echo "- $f"; done)\n\nDans ${svgFile} ?"
  if ./dialog --caption "Sauvegarde" --yesno "$msg"
	then
    tar -czvf ${svgFile} ${fichiers[@]}
  fi
}

##############################

i=0
nbr=${#BdD[@]}

var="./dialog --caption 'Ooohh !!' --theme=dlg.css --menu $(while (($i < $nbr)) ; do echo -n " '${BdD[$i]%:*}' '${BdD[$i]#*:}' " ; ((i++)) ; done)"
while rep=$(eval $var)
  do
    case $rep in
      "") break ;;
       *) $rep ;;
    esac
  done
