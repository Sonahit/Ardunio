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
app.use(logger());

const start = async () => {
    const compiler = webpack(require(path.resolve(config.webpack)));
    const middleware = await koaWebpack({ compiler });
    app .use(middleware)
        .use(serve(path.resolve('dist')))
        .use(cors())
        .listen(config.port, () => {
            console.log(
              "Server Started ->".green,
              "http://localhost:".grey + config.port.toString().blue
            );
          });
}

const startprod = () => {
  const compiler = webpack(require(path.resolve(config.webpack)), (err, stats) => {
    if(stats || err){
      console.log(`${err} /n ${stats}`);
      return;
    }
    app .use(serve(path.resolve('dist')))
        .use(logger)
        .use(cors())
        .listen(config.port, () => {
            console.log(
              "Server Started ->".green,
              "http://localhost:".grey + config.port.toString().blue
            );
        });
  });
  compiler.watch({}, () => {
    console.log('...building');
  })
}

process.env.NODE_ENV === "production" ? startprod() : start();

require('./router')({ app });

module.exports = app;