<template>
  <div class="white elevation-2">
    <v-toolbar flat dense class ="cyan" dark>
      <!--parameters is the only way to go when we're passing project ID to navigate methods! Props are strictly for
      the components!-->
      <v-btn v-if="button=='true'" outline color="indigo" small absolute middle right @click="navigateTo({name:'add-card',params: 
          {projectId: projId}})">
        <slot name ="action"/>
    <v-icon>add</v-icon>
       </v-btn>
       
      <v-toolbar-title>{{title}}</v-toolbar-title>
    </v-toolbar>
 
  <div class="pl-4 pr-4 pt-2 pb-2">
   <slot>
     No slot content defined.
   </slot>
  </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      link: '',
      error: null
    }
  },
  methods: {
        navigateTo(link, board){
            this.$router.push(link)
        }
        },
  props: [
    'title',
    'board',
    'projId',
    'button',
    'buttonAction',
    'teamButton'
      ]
}
</script>
<!--scoped means only works in this vue template, not global, @click when the button
fires a click event, it does the method associated.-->
<style scoped>
</style>   
  <!-- calls the end point, pass it email and password, wait for a response, and opnce we get
the response we print out the data.-->
