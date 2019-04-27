const Router = require('koa-router');
const router = new Router();
const arduino = new Router({
    prefix: "/data"
});

module.exports = ({ app }) => {
    require('./routes/dataArduino')({ arduino });
    router.use('/api', arduino.routes(), arduino.allowedMethods());
    app.use(router.routes()).use(router.allowedMethods());
}