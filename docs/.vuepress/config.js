//to use .env
require('dotenv').config();

//create sidebar
const fs = require('fs');
const path = require('path');

const dirpath = "./docs";
//list to directories for subtree
const dirs = fs.readdirSync(dirpath).filter((f) => {
    //ignore directory start with .
    if(f.charAt(0) === ".") return false;

    return fs.existsSync(dirpath + "/" + f) && fs.statSync(dirpath + "/" + f).isDirectory();
});
//list to under the docs files
const files = fs.readdirSync(dirpath).filter((f) => {
    //READNE.md and index.md skip
    if(f === "README.md" || f === "index.md") return false;
    //ignore not .md and .html files
    if(!( f.endsWith(".md") || f.endsWith(".html"))) return false;
    return fs.existsSync(dirpath + "/" + f) && fs.statSync(dirpath + "/" + f).isFile();
});

//create sidebar array from dirs and files
const sidebarArray = ["/"].concat(dirs.map((dir) => {
    return {
        title: dir,
        collapsable: true,
        children: fs.readdirSync(dirpath + "/" + dir).map((childDir) => {
            return  "/" + dir + "/" + childDir
        })
    }
})).concat(files.map((file) => {
    return  file;
})).sort((a, b) => {
    let aName = typeof a === "string" ? a : a.title;
    let bName = typeof b === "string" ? b : b.title;
    return aName > bName ? 1 : -1;
});

// configure these modules if you
module.exports = {
    title: "VuePress Generated",
    //description : "use for meta description",
    base: "/" + process.env.REPOSITORY + "/",
    config: (md) => {
        md.options.linkify = true
    },
    themeConfig: {
        sidebar: sidebarArray
    }
};

//check for sidebar
console.log(sidebarArray);