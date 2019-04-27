const Koa = require('koa');
const logger = require('koa-logger');
const serve = require('koa-static');
const config = require('./config/config.js')
const app = new Koa();
const koaWebpack = require('koa-webpack');
const webpack = require('webpack');
const path = require('path');
const cors = require('@koa/cors');
require('colors');
const compiler = webpack(require(path.resolve(config.webpack)));
const start = async () => {
    const middleware = await koaWebpack({ compiler });
    app .use(middleware)
        .use(serve(path.resolve('dist')))
        .use(logger)
        .use(cors())
        .listen(config.port, () => {
            console.log(
              "Server Started ->".green,
              "http://localhost:".grey + config.port.toString().blue
            );
          });
}

start();
require('./router')({ app });

module.exports = app;