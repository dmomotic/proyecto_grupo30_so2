axios.defaults.baseURL = 'http://35.239.61.215';

const Proceso = {
  template: /*template*/`
    <div>
    <ul class="list-group" data-bs-toggle="collapse" :data-bs-target="selector" aria-expanded="false" :aria-controls="customId">
      <li class="list-group-item">
        <p class="fw-bold">
          {{ id }} - {{ proceso }} - {{ status }} ({{ hijos.length }})
          <div class="col">
            {{ usuario }} - {{ ram }} MB ~ {{ porcentaje }} %
          </div>
          <div class="col">
            <button type="button" class="btn btn-danger btn-sm" @click.prevent="killProcess(id)">Kill</button>
          </div>
        </p>
      </li>
      <ul class="list-group collapse" :id="customId">
        <li class="list-group-item" v-for="(item, index) in hijos" :key="index">
        {{ item.pid }} - {{ item.name }}
        </li>
      </ul>
    </ul>
    </div>
  `,
  props: [
    'proceso',
    'id',
    'status',
    'hijos', 
    'ram',
    'porcentaje',
    'usuario'
  ],
  data() {
    return {
      customId: 'collapsable' + this.id,
      selector: '#collapsable' + this.id
    }
  },
  methods: {
    killProcess(pid){
      axios.get('/process/kill', {params: {pid}});
    }
  }
}