<template>
    <div>
        <ul>
            <button @click = "setArdData" > Show pin brightness </button>
            <ul>
                <li v-for="(data, index) in sortedArray" :key="index" > 
                Pin : {{ data.pin }} 
                Brightness: {{ data.brightness }} 
                </li>
            </ul> 
            <select v-model="pin">
                <option value="">Select one</option>
                <option value="8">8</option>
                <option value="9">9</option>
                <option value="10">10</option>
                <option value="11">11</option>
                <option value="12">12</option>
                <option value="13">13</option>
            </select>
            <br/>
            <br/>
            <input name="bright" type="range" v-model="brightness" min="0" max="255">
            <label for="bright">Brightness {{brightness}}</label>
        </ul>
        {{ ardData }}
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
                pin: "",
                brightness: "0"
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
                if(this.interval){
                    clearInterval(this.interval);
                }
                this.interval = setInterval( () => {
                    this.getDataArduino().then(data => {
                            if(typeof data === "object"){
                                data = data.data;
                                data.forEach(ledCheck => {
                                    let index = this.ardData.findIndex(led => {
                                        return led.pin === ledCheck.pin
                                    })
                                    if(index >= 0){
                                        if(this.ardData[index].brightness !== ledCheck.brightness){
                                            this.ardData.splice(index, index+1);
                                            this.ardData.splice(index, index+1, ledCheck);  
                                        }
                                    } else {
                                        if(ledCheck.pin !== 0 ){
                                            this.ardData.push(ledCheck);
                                        }
                                    }
                                })           
                            }
                    }).catch(err => {
                    })
                }, 500);
            },
            getDataArduino(){
                    return axios.request({
                        url:"api/data",
                        baseURL: `http://${window.location.hostname}:${config.port}`,
                        headers: {
                            "Access-Control-Allow-Origin": "*",
                        },
                        params: {
                            pin: this.pin,
                            brightness: this.brightness
                        }
                    }).then((resp) => {
                        return resp.data;
                    }).catch(err => {

                    })
            }
        }
    }
</script>



