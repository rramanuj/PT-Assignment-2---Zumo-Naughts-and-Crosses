<template>
<v-layout column>
  
  <v-flex xs6 offset-xs3>
  <div class="white elevation-2">
    <v-toolbar flat dense class ="cyan" dark>
       <v-toolbar-side-icon @click="back()">back</v-toolbar-side-icon>
    <v-toolbar-title>Add Comment</v-toolbar-title>
    </v-toolbar>
    <div>
</div>
  
  <div class="pl-4 pr-4 pt-2 pb-2">

     <v-text-field 
          label="Comment"
          :rules="[() => text.length > 0 || 'This field is required']"
          multi-line v-model="text"></v-text-field>
  
   <v-btn @click="post" dark>Post</v-btn>
  </div>
  </div>
 </v-flex>
</v-layout>
</template>

<script>
import CommentService from '@/services/CommentService'

export default {
  data() {
    return {
    text:null,
    userId: this.$store.state.user._id,
    cardId: this.$store.state.route.params.cardId,
    projectId: this.$store.state.route.params.projectId
        }
    },
  
    methods: {
      back(){
            this.$router.push({name:'card',params: 
            {cardId:this.cardId, projectId: this.projectId
          //found this project id parameter within the vuex program, could probably re-send it for clealiness.
        }})},
    
      async post () {
      //title, description, deadline, userId, owner
      try { 
      (await CommentService.post({text:this.text,userId:this.userId, cardId:this.cardId}))
      this.back();
    } catch (error) {
      this.error = error.response.data;
    }}}
}

</script>
<!--scoped means only works in this vue template, not global, @click when the button
fires a click event, it does the method associated.-->
<style scoped>
.error {
  color:red; 
}


</style>   
  <!-- calls the end point, pass it email and password, wait for a response, and opnce we get
the response we print out the data.-->
