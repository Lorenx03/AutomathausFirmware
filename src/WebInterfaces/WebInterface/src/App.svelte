<script lang="ts">
	import { fade } from 'svelte/transition';
    import Logo from "./lib/logo.svelte";

</script>

<style lang="scss">
	.center{
		position: relative;
		display: flex;
		flex-direction: column;
		align-items: center;
		justify-content: center;
		width: fit-content;
		background-color: white;
		padding: 4rem;
		border-radius: 30px;
		//border: 2px solid rgba(0, 0, 0, 0.1);
		border: 2px solid rgba(0, 0, 0, 0.1);

		h1{
			font-weight: 100;
			line-height: 1;
			font-size: 3.5rem;
			margin-top: 1.5rem;
			margin-bottom: 0.5rem;
		}

		p{
			margin: 0;
			font-weight: 100;
			font-size: 1.4rem;
		}
	}
		
</style>

<div class="center">
	<Logo />
	<h1>Automathaus</h1>
	<p>Ciaociao</p>
</div>