#!/usr/bin/bash

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
  LANG=$2 ./dialog --caption "Sauvegarde" --yesno "Sauvegarder\n$(for f in ${fichiers[@]} ; do echo "- $f"; done)\nDans ${svgFile} ?"
}

##############################

function save_src()
{
  svgFile="/home/jpv/sauvegarde-dialog-$(date +%Y%m%d-%H%M%S).tar.gz"
  fichiers=(\
    dlg.css
    dlg.h
    dlg-main.c
    dlg-menu.c
    dlg.sh
    Makefile
    )
  if kdialog --title "Sauvegarde" --yesnocancel "Sauvegarder\n$(for f in ${fichiers[@]} ; do echo "- $f"; done)\nDans ${svgFile} ?" ; then
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
