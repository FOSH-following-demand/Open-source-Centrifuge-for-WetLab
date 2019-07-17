#!/bin/bash

# abort on errors
set -e

# load .env
eval "$(cat .env <(echo) <(declare -x))"

# build
yarn docs:build

# navigate into the build output directory
cd docs/.vuepress/dist

git init
git add -A
git commit -m 'deploy'


# if you are deploying to https://<USERNAME>.github.io/<REPO>
git push -f https://github.com/FOSH-following-demand/Open-source-Centrifuge-for-WetLab.git master:gh-pages

cd -
