axios.defaults.baseURL = "http://35.226.148.128";

Vue.component("Proceso", Proceso);

new Vue({
  el: '#app',
  mounted() {
    //RAM
    this.chart = new ApexCharts(document.querySelector("#chart"), this.getChartOptions(['ram']))
    this.chart.render()
  },
  beforeDestory() {
    clearInterval(this.interval)
  },
  data() {
    return {
      chart: null,
      seconds: 0,
      data: [],
      ramUsage: 0,
      totalRam: 0,
      totalRamConsumida: 0,
      watchingRam: false,
      cpu: {
        children: [], //{pid, user, state, memory, name, children}
        total: 0,
        ejecucion: 0,
        suspendidos: 0,
        detenidos: 0,
        zombies: 0,
        otros: 0
      },
      watchingCPU: false
    }
  },
  methods: {
    getChartOptions(names) {
      return {
        chart: {
          type: 'line'
        },
        series: names.map((name) => ({name, data: []})),
        xaxis: {
          categories: []
        },
        chart: {
          height: '350px'
        }
      }
    },
    startRAMInfo() {
      this.watchingRam = true;
      this.setInterval()
    },
    stopRAMInfo() {
      this.watchingRam = false;
      this.setInterval()
    },
    fetchRAMData() {
      axios.get('/ram').then((res) => {
        const info = res.data;
        this.totalRamConsumida = Math.round(info.memory_consumed / 1024, 2); 
        this.pushRAMValue(this.totalRamConsumida);
        this.ramUsage = info.percent_use
        this.totalRam = Math.round(info.total_mem / 1024, 2);
      }).catch((e) => {
        console.log(e)
      })
    },
    pushRAMValue(value) {
      if (this.data.length == 25) this.data.splice(0, 1)
      this.data.push(value)
      this.chart.updateSeries([{
        name: 'ram',
        data: this.data
      }])
    },
    fetchCPUData() {
      axios.all([
        axios.get('/cpu')
      ]).then(axios.spread((res1) => {
        const info = res1.data;
        if (info != null) {
          this.cpu = info;
        } else {
          console.log('No se obtuvo la informacion del CPU')
        }
      }))
    },
    setInterval() {
      clearInterval(this.interval)
      const time = 3000
      //cpu && ram
      if (this.watchingCPU && this.watchingRam) {
        this.interval = setInterval(() => {
          this.fetchRAMData()
          this.fetchCPUData()
        }, time)

      }
      //ram
      else if (this.watchingRam) {
        this.interval = setInterval(() => this.fetchRAMData(), time)
      }
      //cpu
      else if (this.watchingCPU) {
        this.interval = setInterval(() => this.fetchCPUData(), time)
      }
    },
    startCPUInfo() {
      this.watchingCPU = true;
      this.setInterval()
    },
    stopCPUInfo() {
      this.watchingCPU = false;
      this.setInterval()
    }
  },
  computed: {
    stripedProgressBarRam() {
      return '';
      // return this.watchingRam ? 'progress-bar-striped' : '';
    }
  }
})