<template>
    <div>
        <ul>
            <span @click = "setArdData" > Show pin brightness </span>
            <ul>
                <li v-for="(data, index) in sortedArray" :key="index" > 
                Pin : {{ data.pin }} 
                Brightness: {{ data.brightness }} 
                </li>
            </ul> 
        </ul>
        
    </div>
</template>

<script>
    import Vue from 'vue';
    import axios from 'axios';
    import config from '../config/config.js';

    export default {
        name: 'App',
        data () {
            return {
                ardData : [],
                interval : 0,
            }
        }, 
        watch : {
            ardData: function (val, oldVal) {
                
            }   
        },
        computed: {
            sortedArray: function () {
                function compare(a, b) {
                if (a.pin < b.pin)
                    return -1;
                if (a.pin > b.pin)
                    return 1;
                return 0;
                }
            return this.ardData.sort(compare);
            }
        },
        methods:
        {
            setArdData() {
                if(this.interval)
                {
                    clearInterval(this.interval);
                }
                this.interval = setInterval( () => {
                    this.getDataArduino().then(data => {
                        if (this.ardData.some(item => {
                        return item.pin === data.pin
                        })) 
                        {
                            this.ardData.forEach(item => {
                                if(item.pin === data.pin)
                                {
                                    item.pin = data.pin;
                                    item.brightness = data.brightness;
                                }
                            })
                        } else {
                            if(data.pin)
                            {
                                this.ardData.push(data);
                            }
                        }
                    });
                    
                }, 30);
            },
            getDataArduino()
            {
                return axios.request({
                    url:"api/data",
                    baseURL: `http://localhost:${config.port}`,
                }).then((resp) => {
                    return resp.data;
                })
            }
        }
    }
</script>



