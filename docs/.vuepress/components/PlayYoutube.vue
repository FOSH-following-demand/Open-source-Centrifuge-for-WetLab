<template>
  <div class="play-youtube">
    <iframe :src="format()" width="100%" height="500px" frameborder="0" ></iframe>
  </div>
</template>

<script>
export default {
  props:['videolink'],
  data(){
    // We have to copy the value because we can't use v-model with
  // nothing to bind to.
  // (VuePress doesn't have support for reactive page variables at the moment.)
    return{
      link: this.videolink,
    }
  },
  methods:{
    format:function(link){
        console.log(this.link.replace(/https:\/\/youtu.be/g, 'https://www.youtube.com/embed'));
        return this.link.replace(/https:\/\/youtu.be/g, 'https://www.youtube.com/embed');
      }
  }

}
</script>
