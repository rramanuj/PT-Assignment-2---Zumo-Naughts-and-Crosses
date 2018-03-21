<template>
    <panel title="Games" class="ml-2">
      <v-btn @click="showAll"
>Show All</v-btn>
      <div
      v-for="project in projects" 
      :key="project._id">
         <v-btn @click="navigateTo({name:'project',
          params: 
          {projectId: project._id}})">
           {{project.title}}
          </v-btn>

      </div>
    </panel>
</template>
<script>

import ProjectService from '@/services/ProjectsService'

export default {
  components: {
   
  },
  data (){
    return {
      projects: null,
      search: '',
      projectId: null,
    }
  }, 
  
  methods: {
        navigateTo(link){
            this.$router.push(link)
        },
       async showAll(){
      this.projects = (await ProjectService.getProjectsByUser({userId:this.$store.state.user._id})).data.data
        }
        
    },
    watch: {
      '$route.query.search' : {
      immediate: true,
       async handler (value) {
         console.log(value);
         if (value != "") {
          this.projects = (await ProjectService.search({userId:this.$store.state.user._id,query:value})).data.data
         }
        }
      }
    },
    async mounted () {
    //do a request to the backend for all the projects
    //always .data, thats how ti returns data.
    this.projects = (await ProjectService.getProjectsByUser({userId:this.$store.state.user._id})).data.data
    }
}

</script>
<!--scoped means only works in this vue template, not global, @click when the button
fires a click event, it does the method associated.-->
<style scoped>
</style>   
  <!-- calls the end point, pass it email and password, wait for a response, and opnce we get
the response we print out the data.-->
