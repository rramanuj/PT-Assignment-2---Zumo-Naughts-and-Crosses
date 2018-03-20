<template>

<v-layout fluid>
<v-flex xs-6>
      <ProjectSearchPanel class="ml-2"/>
       <ProjectsPanel class="mt-2"/>

</v-flex>
  </v-layout>
</template>
<script>

import ProjectService from '@/services/ProjectsService'
import ProjectsPanel from './ProjectsPanel'
import ProjectSearchPanel from './ProjectSearchPanel'

export default {
  components: {
     ProjectsPanel, ProjectSearchPanel //i want to be able to access the panel.
  },
  data (){
    return {
      projects: null,
      search: ''
    }
  }, 

  
  methods: {
        navigateTo(link){
            this.$router.push(link)
        }
    },
    async mounted () {
    //do a request to the backend for all the projects
    //always .data, thats how ti returns data.
    this.projects = (await ProjectService.getProjectsByUser({userId:this.$store.state.user._id})).data.data,
    console.log('projects', this.projects);
    }
}

</script>
<!--scoped means only works in this vue template, not global, @click when the button
fires a click event, it does the method associated.-->
<style scoped>
</style>   
  <!-- calls the end point, pass it email and password, wait for a response, and opnce we get
the response we print out the data.-->
