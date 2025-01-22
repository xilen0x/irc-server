#!/bin/bash
IRC_FOLDER=/home/castorga/my_repos/irc-server

cd $IRC_FOLDER

ACTUAL_BRANCH=$(git rev-parse --abbrev-ref HEAD)

git status
echo ".............................."
git checkout main
git pull
echo ".............................."
git checkout apardo
git pull
echo ".............................."
git checkout linyao
git pull
echo ".............................."
git checkout castorga
git pull
echo ".............................."
git checkout $ACTUAL_BRANCH
echo ".............................."
git status
