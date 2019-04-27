const production = process.env.NODE_ENV === "production";
const path = require('path');
module.exports = {
    production : production,
    port : production ? 8080 : 3000,
    webpack : production ? path.resolve('webpack/webpack.prod.conf.js') : path.resolve('webpack/webpack.dev.conf.js') 
}