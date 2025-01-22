#!/bin/bash
IRC_FOLDER=/home/castorga/my_repos/irc-server

cd $IRC_FOLDER

ACTUAL_BRANCH=$(git rev-parse --abbrev-ref HEAD)

git status
git checkout main
git pull
git checkout apardo
git pull
git checkout castorga
git pull
git checkout linyao
git pull

git checkout $ACTUAL_BRANCH

git status
