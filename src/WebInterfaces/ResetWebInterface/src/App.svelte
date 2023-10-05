<script lang="ts">
	import { fade } from 'svelte/transition';
    import Logo from "./lib/logo.svelte";

	let showPassword: string = "password";
	let SSID: string = "";
	let password: string = "";
	let scanWifi = LoadWifi();


	let submitted: boolean = false;
	function submitForm() {
		submitted = true;

		const payload = {
			SSID: SSID,
			password: password
		};

		const headers = {
			'Content-Type': 'application/json'
		};

		const url = "http://192.168.4.1/submit";
		console.log(JSON.stringify(payload));

		fetch(url, {
			method: 'POST',
			headers: headers,
			body: JSON.stringify(payload)
			})
			.then(response => response.json())
			.then(data => {
				console.log('Response:', data);
			})
			.catch(error => {
				console.error('Error:', error);
			});
	}

	async function LoadWifi() {
        let response = await fetch("http://192.168.4.1/networks");
		let json;

        if (response.ok) { 
            json = await response.json();
			SSID = json.networks[0];
			return json;
        } else {
            alert("HTTP-Error: " + response.status);
        }
    }

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
		border: 1px solid rgba(0, 0, 0, 0.1);

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


		form{
			margin-top: 2rem;
			position: relative;
			display: flex;
			align-items: center;
			flex-direction: column;
			text-align: center;
			font-weight: 100;
			padding: 2rem;
			border-radius: 20px;
			border: 1px solid rgba(0, 0, 0, 0.1);

			label{
				font-size: 1.2rem;
				margin-bottom: 0.4rem;
			}

			select{
				margin-bottom: 1rem;
				border-radius: 10px;
				border: 1px solid rgba(0, 0, 0, 0.2);
				font-size: 1rem;
				padding: 0.25rem 1rem;
				width: 100%;
				background: url("data:image/svg+xml,<svg height='10px' width='10px' viewBox='0 0 16 16' fill='%23000000' xmlns='http://www.w3.org/2000/svg'><path d='M7.247 11.14 2.451 5.658C1.885 5.013 2.345 4 3.204 4h9.592a1 1 0 0 1 .753 1.659l-4.796 5.48a1 1 0 0 1-1.506 0z'/></svg>") no-repeat;
				background-position: calc(100% - 0.75rem) center !important;
				-moz-appearance:none !important;
				-webkit-appearance: none !important; 
				appearance: none !important;
				padding-right: 2rem !important;
			}

			.inline{
				display: flex;
				align-items: center;
				margin-bottom: 1rem;
				gap: 0.5rem;

				input[type=password],input[type=text] {
					border-radius: 10px;
					border: 1px solid rgba(0, 0, 0, 0.2);
					font-size: 1rem;
					padding: 0.4rem 1rem;
					transition: 500ms;
				}

				button{
					aspect-ratio: 1/1;
					background-color: white;
					border: 1px solid rgba(0, 0, 0, 0.2);
					border-radius: 100%;
					display: flex;
					align-items: center;
					justify-content: center;
				}
			}

			input[type=submit]:hover{
				transform: scale(1.1);
				background-color: #1B1B1B;
				color: white;
			}

			input[type=submit] {
				border-radius: 50px;
				margin-top: 0.3rem;
				color: #1B1B1B;
				border: 1px solid rgba(0, 0, 0, 0.4);
				font-size: 1.3rem;
				padding: 0.5rem 2rem;
				font-weight: 200;
				background-color: white;
				font-family: sans-serif;
				transition: 500ms;
				width: fit-content;
				cursor: pointer;
			}
		}

		.successMess{
			background-color: white;
			flex-flow: column;
			position: absolute;
			top: 0;
			left: 0;
			border-radius: 20px;
			height: 100%;
			width: 100%;
			display: flex;
			align-items: center;
			justify-content: center;

			p{
				font-size: 1.7rem;
				font-weight: 200;
			}
		}
	}
</style>

<div class="center">
	<Logo />
	<h1>Automathaus</h1>
	<p>Ops.. non riesco a connettermi..</p>

	<form id="netForm" on:submit|preventDefault={submitForm}>
		<label for="netw">Scegli un access point </label>
		<select id="netw" name="netw" required bind:value={SSID}>

			{#await scanWifi}
				<option value="" selected disabled> Scanning networks... </option>
			{:then networksObj} 
				{#each networksObj.networks as network, i}
					{#if i == 0}
						<option value="{network}" selected> {network} </option>
					{:else}
						<option value="{network}"> {network} </option>
					{/if}
				{/each}
			{:catch error}
				<option value="" selected disabled> Networks not found! </option>
			{/await}
			
		</select>

		<label for="password">Password</label>
		<div class="inline">
			{#if showPassword == "password"}
				<input type="password" required placeholder="••••••••" id="password" name="password" bind:value={password}>
			{:else}
				<input type="text" required placeholder="••••••••" id="password" name="password" bind:value={password}>
			{/if} 
			<button on:click|preventDefault={() => showPassword = (showPassword == "password") ? "text" : "password"}>
				{#if showPassword == "password"}
					<svg xmlns="http://www.w3.org/2000/svg" width="1rem" height="1rem" viewBox="0 0 24 24"><path fill="currentColor" d="M12 9a3 3 0 0 0-3 3a3 3 0 0 0 3 3a3 3 0 0 0 3-3a3 3 0 0 0-3-3m0 8a5 5 0 0 1-5-5a5 5 0 0 1 5-5a5 5 0 0 1 5 5a5 5 0 0 1-5 5m0-12.5C7 4.5 2.73 7.61 1 12c1.73 4.39 6 7.5 11 7.5s9.27-3.11 11-7.5c-1.73-4.39-6-7.5-11-7.5Z"/></svg>
				{:else}
					<svg xmlns="http://www.w3.org/2000/svg" width="1rem" height="1rem" viewBox="0 0 24 24"><path fill="currentColor" d="M11.83 9L15 12.16V12a3 3 0 0 0-3-3h-.17m-4.3.8l1.55 1.55c-.05.21-.08.42-.08.65a3 3 0 0 0 3 3c.22 0 .44-.03.65-.08l1.55 1.55c-.67.33-1.41.53-2.2.53a5 5 0 0 1-5-5c0-.79.2-1.53.53-2.2M2 4.27l2.28 2.28l.45.45C3.08 8.3 1.78 10 1 12c1.73 4.39 6 7.5 11 7.5c1.55 0 3.03-.3 4.38-.84l.43.42L19.73 22L21 20.73L3.27 3M12 7a5 5 0 0 1 5 5c0 .64-.13 1.26-.36 1.82l2.93 2.93c1.5-1.25 2.7-2.89 3.43-4.75c-1.73-4.39-6-7.5-11-7.5c-1.4 0-2.74.25-4 .7l2.17 2.15C10.74 7.13 11.35 7 12 7Z"/></svg>
				{/if} 
			</button>
		</div>
		<input type="submit" value="Connetti">

		{#if submitted == true}
			<div class="successMess" transition:fade>
				<p>
					Riavvio...
				</p>
			</div>
		{/if}
	</form>
</div>