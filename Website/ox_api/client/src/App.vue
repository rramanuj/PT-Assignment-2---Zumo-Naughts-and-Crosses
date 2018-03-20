<template>
  <div id="app">
    <v-app>
      <page-header />
        <v-container fluid>
            <router-view/>

        </v-container>

    </v-app>
  </div>
</template>

<script>
import PageHeader from '@/components/Header.vue'
export default {
  name: 'App',
  components:{
    PageHeader
  }
};
</script>
<!--sets an underline -->
<style>
/*.input-group--text-field input { 
  border-bottom: 1px solid black;
}*/

/*.toolbar__title {
  color: white;

}
.btn_content {
  color: white;
}*/

#app {
  font-family: 'Avenir', Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
}


</style>
