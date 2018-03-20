<template>
    <panel title="Search">
            <v-text-field label="Search by Project.." v-model="search"></v-text-field>
    </panel>
</template>
<script>
export default {
  data () {
    return {
      search: ''
    }
  },
  watch: {
    search (value){
      const route = {
        name: 'projects'
      }
      if (this.search !== '') {
        route.query = {
          search: this.search
        }
      }
     this.$router.push(route)
    }
  }
}
</script>
<!--scoped means only works in this vue template, not global, @click when the button
fires a click event, it does the method associated.-->
<style scoped>
</style>   
  <!-- calls the end point, pass it email and password, wait for a response, and opnce we get
the response we print out the data.-->
